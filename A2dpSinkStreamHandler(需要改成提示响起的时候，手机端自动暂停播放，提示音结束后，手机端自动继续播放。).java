/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.android.bluetooth.a2dpsink;

import android.bluetooth.BluetoothDevice;
import android.content.Context;
import android.media.AudioAttributes;
import android.media.AudioFocusRequest;
import android.media.AudioManager;
import android.media.AudioManager.OnAudioFocusChangeListener;
import android.os.Handler;
import android.os.Message;
import android.util.Log;

import com.android.bluetooth.avrcpcontroller.AvrcpControllerService;
import com.android.bluetooth.R;

import java.util.List;

/**
 * Bluetooth A2DP SINK Streaming Handler.
 *
 * This handler defines how the stack behaves once the A2DP connection is established and both
 * devices are ready for streaming. For simplification we assume that the connection can either
 * stream music immediately (i.e. data packets coming in or have potential to come in) or it cannot
 * stream (i.e. Idle and Open states are treated alike). See Fig 4-1 of GAVDP Spec 1.0.
 *
 * Note: There are several different audio tracks that a connected phone may like to transmit over
 * the A2DP stream including Music, Navigation, Assistant, and Notifications.  Music is the only
 * track that is almost always accompanied with an AVRCP play/pause command.
 *
 * Streaming is initiated by either an explicit play command from user interaction or audio coming
 * from the phone.  Streaming is terminated when either the user pauses the audio, the audio stream
 * from the phone ends, the phone disconnects, or audio focus is lost.  During playback if there is
 * a change to audio focus playback may be temporarily paused and then resumed when focus is
 * restored.
 */
public class A2dpSinkStreamHandler extends Handler {
    private static final boolean DBG = true;
    private static final String TAG = "A2dpSinkStreamHandler";

    // Configuration Variables
    private static final int DEFAULT_DUCK_PERCENT = 25;

    // Incoming events.
    public static final int SRC_STR_START = 0; // Audio stream from remote device started
    public static final int SRC_STR_STOP = 1; // Audio stream from remote device stopped
    public static final int SNK_PLAY = 2; // Play command was generated from local device
    public static final int SNK_PAUSE = 3; // Pause command was generated from local device
    public static final int SRC_PLAY = 4; // Play command was generated from remote device
    public static final int SRC_PAUSE = 5; // Pause command was generated from remote device
    public static final int DISCONNECT = 6; // Remote device was disconnected
    public static final int AUDIO_FOCUS_CHANGE = 7; // Audio focus callback with associated change

    // Used to indicate focus lost
    private static final int STATE_FOCUS_LOST = 0;
    // Used to inform bluedroid that focus is granted
    private static final int STATE_FOCUS_GRANTED = 1;

    // Private variables.
    private A2dpSinkStateMachine mA2dpSinkSm;
    private Context mContext;
    private AudioManager mAudioManager;
    // Keep track if the remote device is providing audio
    private boolean mStreamAvailable = false;
    private boolean mSentPause = false;
    // Keep track of the relevant audio focus (None, Transient, Gain)
    private int mAudioFocus = AudioManager.AUDIOFOCUS_NONE;

    // Focus changes when we are currently holding focus.
    private OnAudioFocusChangeListener mAudioFocusListener = new OnAudioFocusChangeListener() {
        public void onAudioFocusChange(int focusChange) {
            if (DBG) {
                Log.d(TAG, "onAudioFocusChangeListener focuschange " + focusChange);
            }
            A2dpSinkStreamHandler.this.obtainMessage(AUDIO_FOCUS_CHANGE, focusChange)
                    .sendToTarget();
        }
    };

    public A2dpSinkStreamHandler(A2dpSinkStateMachine a2dpSinkSm, Context context) {
        mA2dpSinkSm = a2dpSinkSm;
        mContext = context;
        mAudioManager = (AudioManager) context.getSystemService(Context.AUDIO_SERVICE);
    }

    @Override
    public void handleMessage(Message message) {
        if (DBG) {
            Log.d(TAG, " process message: " + message.what);
            Log.d(TAG, " audioFocus =  " + mAudioFocus);
        }
        switch (message.what) {
            case SRC_STR_START:
                // Audio stream has started, stop it if we don't have focus.
                mStreamAvailable = true;
                if (mAudioFocus == AudioManager.AUDIOFOCUS_NONE) {
                    //sendAvrcpPause();
                    //requestAudioFocus();
                } 
				//else {
                    startAvrcpUpdates();
                //}
                break;

            case SRC_STR_STOP:
                // Audio stream has stopped, maintain focus but stop avrcp updates.
                mStreamAvailable = false;
                stopAvrcpUpdates();
                break;

            case SNK_PLAY:
                // Local play command, gain focus and start avrcp updates.
                if (mAudioFocus == AudioManager.AUDIOFOCUS_NONE) {
                    requestAudioFocus();
                }
                startAvrcpUpdates();
                break;

            case SNK_PAUSE:
                // Local pause command, maintain focus but stop avrcp updates.
                stopAvrcpUpdates();
                break;

            case SRC_PLAY:
                // Remote play command, if we have audio focus update avrcp, otherwise send pause.
                if (mAudioFocus == AudioManager.AUDIOFOCUS_NONE) {
                    //sendAvrcpPause();
                    requestAudioFocus();
                }
				//else {
                    startAvrcpUpdates();
                //}
                break;

            case SRC_PAUSE:
                // Remote pause command, stop avrcp updates.
                stopAvrcpUpdates();
                break;

            case DISCONNECT:
                // Remote device has disconnected, restore everything to default state.
                //sendAvrcpPause();
                stopAvrcpUpdates();
                abandonAudioFocus();
                mSentPause = false;
                break;

            case AUDIO_FOCUS_CHANGE:
                // message.obj is the newly granted audio focus.
                switch ((int) message.obj) {
                    case AudioManager.AUDIOFOCUS_GAIN:
                        // Begin playing audio, if we paused the remote, send a play now.
                        startAvrcpUpdates();
                        startFluorideStreaming();
                        if (mSentPause) {
                            sendAvrcpPlay();
                            mSentPause = false;
                        }
                        break;

                    case AudioManager.AUDIOFOCUS_LOSS_TRANSIENT_CAN_DUCK:
                        // Make the volume duck.
                        int duckPercent = mContext.getResources().getInteger(
                                R.integer.a2dp_sink_duck_percent);
                        if (duckPercent < 0 || duckPercent > 100) {
                            Log.e(TAG, "Invalid duck percent using default.");
                            duckPercent = DEFAULT_DUCK_PERCENT;
                        }
                        float duckRatio = (duckPercent / 100.0f);
                        if (DBG) {
                            Log.d(TAG, "Setting reduce gain on transient loss gain=" + duckRatio);
                        }
                        setFluorideAudioTrackGain(duckRatio);
                        break;

                    case AudioManager.AUDIOFOCUS_LOSS_TRANSIENT:
                        // Temporary loss of focus, if we are actively streaming pause the remote
                        // and make sure we resume playback when we regain focus.
                        if (mStreamAvailable) {
                            sendAvrcpPause();
                            mSentPause = true;
                        }
                        stopFluorideStreaming();
                        break;

                    case AudioManager.AUDIOFOCUS_LOSS:
                        // Permanent loss of focus probably due to another audio app, abandon focus
                        // and stop playback.
                        mAudioFocus = AudioManager.AUDIOFOCUS_NONE;
                        abandonAudioFocus();
                        sendAvrcpPause();
						mSentPause = true;
                        break;
                }
                break;

            default:
                Log.w(TAG, "Received unexpected event: " + message.what);
        }
    }

    /**
     * Utility functions.
     */
    private int requestAudioFocus() {
        // Bluetooth A2DP may carry Music, Audio Books, Navigation, or other sounds so mark content
        // type unknown.
        AudioAttributes streamAttributes =
                new AudioAttributes.Builder()
                        .setUsage(AudioAttributes.USAGE_MEDIA)
                        .setContentType(AudioAttributes.CONTENT_TYPE_UNKNOWN)
                        .build();
        // Bluetooth ducking is handled at the native layer so tell the Audio Manger to notify the
        // focus change listener via .setWillPauseWhenDucked().
        AudioFocusRequest focusRequest =
                new AudioFocusRequest.Builder(AudioManager.AUDIOFOCUS_GAIN)
                        .setAudioAttributes(streamAttributes)
                        .setWillPauseWhenDucked(true)
                        .setOnAudioFocusChangeListener(mAudioFocusListener, this)
                        .build();
        int focusRequestStatus = mAudioManager.requestAudioFocus(focusRequest);
        // If the request is granted begin streaming immediately and schedule an upgrade.
        if (focusRequestStatus == AudioManager.AUDIOFOCUS_REQUEST_GRANTED) {
            startAvrcpUpdates();
            startFluorideStreaming();
            mAudioFocus = AudioManager.AUDIOFOCUS_GAIN;
        }
        return focusRequestStatus;
    }


    private void abandonAudioFocus() {
        stopFluorideStreaming();
        mAudioManager.abandonAudioFocus(mAudioFocusListener);
        mAudioFocus = AudioManager.AUDIOFOCUS_NONE;
    }

    private void startFluorideStreaming() {
        mA2dpSinkSm.informAudioFocusStateNative(STATE_FOCUS_GRANTED);
        mA2dpSinkSm.informAudioTrackGainNative(1.0f);
    }

    private void stopFluorideStreaming() {
        mA2dpSinkSm.informAudioFocusStateNative(STATE_FOCUS_LOST);
    }

    private void setFluorideAudioTrackGain(float gain) {
        mA2dpSinkSm.informAudioTrackGainNative(gain);
    }

    private void startAvrcpUpdates() {
        // Since AVRCP gets started after A2DP we may need to request it later in cycle.
        AvrcpControllerService avrcpService = AvrcpControllerService.getAvrcpControllerService();

        if (DBG) {
            Log.d(TAG, "startAvrcpUpdates");
        }
        if (avrcpService != null && avrcpService.getConnectedDevices().size() == 1) {
            avrcpService.startAvrcpUpdates();
        } else {
            Log.e(TAG, "startAvrcpUpdates failed because of connection.");
        }
    }

    private void stopAvrcpUpdates() {
        // Since AVRCP gets started after A2DP we may need to request it later in cycle.
        AvrcpControllerService avrcpService = AvrcpControllerService.getAvrcpControllerService();

        if (DBG) {
            Log.d(TAG, "stopAvrcpUpdates");
        }
        if (avrcpService != null && avrcpService.getConnectedDevices().size() == 1) {
            avrcpService.stopAvrcpUpdates();
        } else {
            Log.e(TAG, "stopAvrcpUpdates failed because of connection.");
        }
    }

    private void sendAvrcpPause() {
        // Since AVRCP gets started after A2DP we may need to request it later in cycle.
        AvrcpControllerService avrcpService = AvrcpControllerService.getAvrcpControllerService();

        if (DBG) {
            Log.d(TAG, "sendAvrcpPause");
        }
        if (avrcpService != null) {
            List<BluetoothDevice> connectedDevices = avrcpService.getConnectedDevices();
            if (!connectedDevices.isEmpty()) {
                BluetoothDevice targetDevice = connectedDevices.get(0);
                if (DBG) {
                    Log.d(TAG, "Pausing AVRCP.");
                }
                avrcpService.sendPassThroughCmd(targetDevice,
                        AvrcpControllerService.PASS_THRU_CMD_ID_PAUSE,
                        AvrcpControllerService.KEY_STATE_PRESSED);
                avrcpService.sendPassThroughCmd(targetDevice,
                        AvrcpControllerService.PASS_THRU_CMD_ID_PAUSE,
                        AvrcpControllerService.KEY_STATE_RELEASED);
            }
        } else {
            Log.e(TAG, "Passthrough not sent, connection un-available.");
        }
    }

    private void sendAvrcpPlay() {
        // Since AVRCP gets started after A2DP we may need to request it later in cycle.
        AvrcpControllerService avrcpService = AvrcpControllerService.getAvrcpControllerService();

        if (DBG) {
            Log.d(TAG, "sendAvrcpPlay");
        }
        if (avrcpService != null) {
            List<BluetoothDevice> connectedDevices = avrcpService.getConnectedDevices();
            if (!connectedDevices.isEmpty()) {
                BluetoothDevice targetDevice = connectedDevices.get(0);
                if (DBG) {
                    Log.d(TAG, "Playing AVRCP.");
                }
                avrcpService.sendPassThroughCmd(targetDevice,
                        AvrcpControllerService.PASS_THRU_CMD_ID_PLAY,
                        AvrcpControllerService.KEY_STATE_PRESSED);
                avrcpService.sendPassThroughCmd(targetDevice,
                        AvrcpControllerService.PASS_THRU_CMD_ID_PLAY,
                        AvrcpControllerService.KEY_STATE_RELEASED);
            }
        } else {
            Log.e(TAG, "Passthrough not sent, connection un-available.");
        }
    }
}
