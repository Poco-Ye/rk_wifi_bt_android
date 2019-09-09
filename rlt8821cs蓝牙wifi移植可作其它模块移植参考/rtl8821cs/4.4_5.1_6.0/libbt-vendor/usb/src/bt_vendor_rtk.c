/******************************************************************************
 *
 *  Copyright (C) 2009-2012 Broadcom Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at:
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 ******************************************************************************/

/******************************************************************************
 *
 *  Filename:      bt_vendor_rtk.c
 *
 *  Description:   Broadcom vendor specific library implementation
 *
 ******************************************************************************/

#define LOG_TAG "bt_vendor_usb"
#define RTKBT_RELEASE_NAME "20181224_BT_ANDROID_7.0"

#include <fcntl.h>
#include <errno.h>
#include <utils/Log.h>
#include "bt_vendor_rtk.h"

#include <errno.h>
#include <sys/ioctl.h>

#ifndef BTVND_DBG
#define BTVND_DBG FALSE
#endif

#if (BTVND_DBG == TRUE)
#define BTVNDDBG(param, ...) {ALOGD(param, ## __VA_ARGS__);}
#else
#define BTVNDDBG(param, ...) {}
#endif



//Define ioctl cmd the same as HCIDEVUP in the kernel
#define DOWN_FW_CFG  _IOW('H', 201, int)


/******************************************************************************
**  Local type definitions
******************************************************************************/
#define VND_PORT_NAME_MAXLEN    256
/* vendor serial control block */
typedef struct
{
    int fd;                     /* fd to Bluetooth device */
    uint16_t dev_id;
    char port_name[VND_PORT_NAME_MAXLEN];
} vnd_userial_cb_t;

/******************************************************************************
**  Variables
******************************************************************************/

bt_vendor_callbacks_t *bt_vendor_cbacks = NULL;
uint8_t vnd_local_bd_addr[6]={0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static vnd_userial_cb_t vnd_userial;

/*****************************************************************************
**
**   BLUETOOTH VENDOR INTERFACE LIBRARY FUNCTIONS
**
*****************************************************************************/

static int init(const bt_vendor_callbacks_t* p_cb, unsigned char *local_bdaddr,char *bt_device_node)
{
    ALOGI("RTKBT_RELEASE_NAME: %s",RTKBT_RELEASE_NAME);
    ALOGI("init");

    if (p_cb == NULL)
    {
        ALOGE("init failed with no user callbacks!");
        return -1;
    }

    userial_vendor_init(bt_device_node);

    /* store reference to user callbacks */
    bt_vendor_cbacks = (bt_vendor_callbacks_t *) p_cb;

    /* This is handed over from the stack */
    memcpy(vnd_local_bd_addr, local_bdaddr, 6);

    return 0;
}



/** Requested operations */
static int op(bt_vendor_opcode_t opcode, void *param)
{
    int retval = 0;

    BTVNDDBG("op for %d", opcode);

    switch(opcode)
    {
        case BT_VND_OP_POWER_CTRL:
            {
                return 0;
            }
            break;

        case BT_VND_OP_FW_CFG:
            {
				ALOGE("Bt_vendor_rtk Op for BT_VND_OP_FW_CFG");
				retval = ioctl(vnd_userial.fd, DOWN_FW_CFG, NULL);
				if(retval>0){
					ALOGE("Bt_vendor_rtk Download Fw Success");
					bt_vendor_cbacks->fwcfg_cb(BT_VND_OP_RESULT_SUCCESS);
				}else{
					ALOGE("Bt_vendor_rtk Download Fw failed: %s(%d)", strerror(errno), errno);
					bt_vendor_cbacks->fwcfg_cb(BT_VND_OP_RESULT_FAIL);
				}
            }
			break;


        case BT_VND_OP_SCO_CFG:
            {
                retval = -1;
            }
            break;

        case BT_VND_OP_USERIAL_OPEN:
            {
                int (*fd_array)[] = (int (*)[]) param;
                int fd, idx;
                fd = userial_vendor_open();
                if (fd != -1)
                {
                    for (idx=0; idx < CH_MAX; idx++)
                        (*fd_array)[idx] = fd;

                    retval = 1;
                }
                /* retval contains numbers of open fd of HCI channels */
            }
            break;

        case BT_VND_OP_USERIAL_CLOSE:
            {
                userial_vendor_close();
            }
            break;

        case BT_VND_OP_GET_LPM_IDLE_TIMEOUT:
            {
                uint32_t *timeout_ms = (uint32_t *) param;
                *timeout_ms = 250;
            }
            break;

        case BT_VND_OP_LPM_SET_MODE:
            {
        		if (bt_vendor_cbacks)
        			bt_vendor_cbacks->lpm_cb(BT_VND_OP_RESULT_SUCCESS);
            }
            break;

        case BT_VND_OP_LPM_WAKE_SET_STATE:
            break;

        case BT_VND_OP_EPILOG:
            {

					if (bt_vendor_cbacks)
					{
						bt_vendor_cbacks->epilog_cb(BT_VND_OP_RESULT_SUCCESS);
					}
            }
            break;
    }

    return retval;
}

/*******************************************************************************
**
** Function        userial_vendor_init
**
** Description     Initialize userial vendor-specific control block
**
** Returns         None
**
*******************************************************************************/
void userial_vendor_init(char *bt_device_node)
{
    vnd_userial.fd = -1;
    vnd_userial.dev_id = 0;
    snprintf(vnd_userial.port_name, VND_PORT_NAME_MAXLEN, "%s", \
            bt_device_node);
}

/*******************************************************************************
**
** Function        userial_vendor_open
**
** Description     Open the serial port with the given configuration
**
** Returns         device fd
**
*******************************************************************************/
int userial_vendor_open(void)
{
	ALOGI("userial vendor open: opening %s", vnd_userial.port_name);

	if ((vnd_userial.fd = open(vnd_userial.port_name, O_RDWR)) == -1)
	{
	    ALOGE("userial vendor open: unable to open %s: %s", vnd_userial.port_name, strerror(errno));
	    return -1;
	}

	ALOGI("device fd = %d open", vnd_userial.fd);

	return vnd_userial.fd;
}

/*******************************************************************************
**
** Function        userial_vendor_close
**
** Description     Conduct vendor-specific close work
**
** Returns         None
**
*******************************************************************************/
void userial_vendor_close(void)
{
    int result;

    if (vnd_userial.fd == -1)
        return;

    ALOGI("device fd = %d close", vnd_userial.fd);

    if ((result = close(vnd_userial.fd)) < 0)
        ALOGE( "close(fd:%d) FAILED result:%d", vnd_userial.fd, result);

    vnd_userial.fd = -1;
}

/** Closes the interface */
static void cleanup( void )
{
    BTVNDDBG("cleanup");
    bt_vendor_cbacks = NULL;
}

// Entry point of DLib
const bt_vendor_interface_t BLUETOOTH_VENDOR_LIB_INTERFACE = {
    sizeof(bt_vendor_interface_t),
    init,
    op,
    cleanup
};
