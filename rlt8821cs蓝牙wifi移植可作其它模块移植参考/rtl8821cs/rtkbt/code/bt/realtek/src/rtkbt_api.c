#define LOG_TAG "RTKBT_API"
#ifdef BLUETOOTH_RTK_API
#include <string.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <pthread.h>

#include <hardware/bluetooth.h>
#include "hardware/bt_rtkbt.h"
//#include "bt_target.h"
//#include "bt_trace.h"
#include "btif_common.h"
#include "rtkbt_api.h"
#include "btif_storage.h"
#include "uipc.h"
#include "btcore/include/module.h"

enum {
    EVENT_GENERIC = 1,
};

static rtkbt_callbacks_t * rtkbt_callbacks = NULL;
static pthread_mutexattr_t rtkbt_mutexattr;
static pthread_mutex_t rtkbt_mutex;
static bool stopServiceFlag = false;
extern int rtkbt_loadconfig(char * path);
extern int rtkbt_conf_init();
extern int rtkbt_conf_exit();

#include "uipc.h"
static char * rtkbt_UipcPath[UIPC_CH_NUM];
char * rtkbt_api_GetUipcPath(int ch_id)
{
    return rtkbt_UipcPath[ch_id];
}
int rtkbt_api_SetUipcPath(int ch_id, char * path)
{
    if((ch_id < UIPC_CH_ID_RTKBT_CHANNEL_1)||(ch_id > UIPC_CH_ID_RTKBT_CHANNEL_6))
    {
        ALOGE("%s ch_id(%d) is out of range,UIPC_CH_ID_RTKBT_CHANNEL_1=%d UIPC_CH_ID_RTKBT_CHANNEL_6=%d\n", __FUNCTION__, ch_id, UIPC_CH_ID_RTKBT_CHANNEL_1, UIPC_CH_ID_RTKBT_CHANNEL_6);
        return -1;
    }
    char * buffer = malloc(strlen(path)+1);
    if(buffer == NULL)
    {
        BTIF_TRACE_ERROR("%s GKI_getbuf return NULL", __FUNCTION__);
        return -1;
    }
    strcpy(buffer, path);
    rtkbt_UipcPath[ch_id] = buffer;
    return 0;
}

static rtkbt_api_Hook_func rtkbt_Hook_funcs[RTKBT_MAX_ID] = {0};
int rtkbt_api_Hook(int event, void* arg, int len)
{
    int i,res = 0;
    pthread_mutex_lock(&rtkbt_mutex);
    for(i=1; i< RTKBT_MAX_ID; i++)
    {
        if(rtkbt_Hook_funcs[i])
        {
            res |= rtkbt_Hook_funcs[i](event, arg, len);
        }
    }
    pthread_mutex_unlock(&rtkbt_mutex);
    if(stopServiceFlag && event == RTKBT_HOOK_DISABLE_BT_COMPLETE)
        memset(rtkbt_Hook_funcs, 0, sizeof(rtkbt_Hook_funcs));
    return res;
}
int rtkbt_api_RegisterHook(int id, rtkbt_api_Hook_func handler)
{
    if((id<0)||(id>=RTKBT_MAX_ID))
    {
        BTIF_TRACE_ERROR("%s id(%d) is out of range,RTKBT_MAX_ID=%d\n", __FUNCTION__, id, RTKBT_MAX_ID);
        return -1;
    }
    BTIF_TRACE_API("%s", __FUNCTION__);
    pthread_mutex_lock(&rtkbt_mutex);
    rtkbt_Hook_funcs[id] = handler;
    pthread_mutex_unlock(&rtkbt_mutex);
    return 0;
}

static rtkbt_api_Plugin_comm_func rtkbt_Plugin_comm_funcs[RTKBT_MAX_ID] = {0};
/*************************************************************************************************************
    **
    ** Function         rtkbt_api_RegisterPluginExMsg
    **
    ** Description     plugins need to communicate with each other for some reason, register the func to rtkbt_api.c
    ** Arguments      id: plugin id(RTKBT_AUTOPAIR_ID,RTKBT_VR_ID, etc.)
    **                      handler: callback
    ** Returns          0-success/other-fail
    **
**************************************************************************************************************/
int rtkbt_api_RegisterPluginExMsg(int id, rtkbt_api_Plugin_comm_func handler) {
    BTIF_TRACE_API("%s", __FUNCTION__);
    if((id<0)||(id>=RTKBT_MAX_ID))
    {
        BTIF_TRACE_ERROR("%s id(%d) is out of range,RTKBT_MAX_ID=%d\n", __FUNCTION__, id, RTKBT_MAX_ID);
        return -1;
    }
    pthread_mutex_lock(&rtkbt_mutex);
    rtkbt_Plugin_comm_funcs[id] = handler;
    pthread_mutex_unlock(&rtkbt_mutex);
    return 0;
}

int rtkbt_api_Send_PluginMsg(int id, int event, tPlugin_comm * plugin_arg) {
    BTIF_TRACE_API("%s", __FUNCTION__);
    int i,res;
    pthread_mutex_lock(&rtkbt_mutex);
    if(id == RTKBT_PLUGIN_BC) {
        for(i = 0; i < RTKBT_MAX_ID; i++) {
            if(rtkbt_Plugin_comm_funcs[i])
                rtkbt_Plugin_comm_funcs[i](i,event,plugin_arg);
        }
        res = 0;
    }
    else{
        if((id<0)||(id>=RTKBT_MAX_ID))
        {
            BTIF_TRACE_ERROR("%s id(%d) is out of range,RTKBT_MAX_ID=%d\n", __FUNCTION__, id, RTKBT_MAX_ID);
            res = -1;
        }

        if(rtkbt_Plugin_comm_funcs[id]) {
            res = rtkbt_Plugin_comm_funcs[id](id,event,plugin_arg);;
        }
        else
            res = -1;
    }
    pthread_mutex_unlock(&rtkbt_mutex);
    return res;
}

static rtkbt_api_GenericCommand_func rtkbt_GenericCommand_funcs[RTKBT_MAX_ID] = {0};
int rtkbt_api_RegisterGenericCommand(int id, rtkbt_api_GenericCommand_func handler)
{
    BTIF_TRACE_API("%s", __FUNCTION__);
    if((id<0)||(id>=RTKBT_MAX_ID))
    {
        BTIF_TRACE_ERROR("%s id(%d) is out of range,RTKBT_MAX_ID=%d\n", __FUNCTION__, id, RTKBT_MAX_ID);
        return -1;
    }
    pthread_mutex_lock(&rtkbt_mutex);
    rtkbt_GenericCommand_funcs[id] = handler;
    pthread_mutex_unlock(&rtkbt_mutex);
    return 0;
}
static int rtkbt_GenericCommand(int id, int command, unsigned char * data, int len)
{
    int res;
    BTIF_TRACE_API("%s(%d,%d,*,%d)", __FUNCTION__, id, command, len);
    if((id<0)||(id>=RTKBT_MAX_ID))
    {
        BTIF_TRACE_ERROR("%s id(%d) is out of range,RTKBT_MAX_ID=%d\n", __FUNCTION__, id, RTKBT_MAX_ID);
        return -9998;
    }
    pthread_mutex_lock(&rtkbt_mutex);
    if(rtkbt_GenericCommand_funcs[id])
        res = rtkbt_GenericCommand_funcs[id](id, command, data, len);
    else
        res = -9999;
    pthread_mutex_unlock(&rtkbt_mutex);
    return res;
}
/*
    every plugin must register rtkbt_GenericCommand.
    JNI check features by GetFeature.
    0- not supported /other-supported
*/
static int rtkbt_GetFeature(int id)
{
    int res = 0;
    BTIF_TRACE_API("%s(%d)", __FUNCTION__, id);
    if((id<0)||(id>=RTKBT_MAX_ID))
    {
        BTIF_TRACE_ERROR("%s id(%d) is out of range,RTKBT_MAX_ID=%d\n", __FUNCTION__, id, RTKBT_MAX_ID);
        return 0;
    }
    pthread_mutex_lock(&rtkbt_mutex);
    if((id>0)&&(id<RTKBT_MAX_ID))
        res = (rtkbt_GenericCommand_funcs[id]?1:0);
    pthread_mutex_unlock(&rtkbt_mutex);
    return res;
}
/*
    internal function
    it must execute in btif task
*/
static void rtkbt_SendGenericEvent(char* p_param)
{
    int * p;
    int id,event,len;

    p = (int*)p_param;
    id = *p++;
    event = *p++;
    len = *p++;
    BTIF_TRACE_ERROR("rtkbt_SendGenericEvent(%d,%d,%08x,%d)\n", id, event, p, len);

    if(rtkbt_callbacks && rtkbt_callbacks->onGenericEvent)
        rtkbt_callbacks->onGenericEvent(id, event, (unsigned char *)p, len);
    return;
}
/*
    internal function
    it must execute in btif task
*/
static void rtkbt_SendEvent(UINT16 event, char* p_param)
{
    BTIF_TRACE_ERROR("rtkbt_SendEvent(%d,%08x)\n", event, p_param);
    switch(event)
    {
        case EVENT_GENERIC:
            rtkbt_SendGenericEvent(p_param);
            break;
        default:
            break;
    }
    return;
}
/*
    api, it's used by plugin or bluedroid
*/
int rtkbt_api_SendGenericEvent(int id, int event, unsigned char * data, int len)
{
    char buffer[1024];
    int * ip;
    if((id<0)||(id>=RTKBT_MAX_ID))
    {
        BTIF_TRACE_ERROR("%s id(%d) is out of range,RTKBT_MAX_ID=%d\n", __FUNCTION__, id, RTKBT_MAX_ID);
        return -1;
    }

    BTIF_TRACE_API("rtkbt_api_SendGenericEvent(%d,%d,%08x,%d)\n", id, event, data, len);
    if(len > 1000)
    {
        BTIF_TRACE_ERROR("rtkbt_api_SendGenericEvent(%d,%d,%08x,%d) len too long\n", id, event, data, len);
        return -1;
    }
    if(rtkbt_callbacks && rtkbt_callbacks->onGenericEvent)
    {
        ip = (int *)buffer;
        *ip++ = id;
        *ip++ = event;
        *ip++ = len;
        memcpy(ip, data, len);
        btif_transfer_context(rtkbt_SendEvent,EVENT_GENERIC, buffer, (len+12), 0);
    }else
        BTIF_TRACE_ERROR("rtkbt_api_SendGenericEvent(%d,%d,%08x,%d) rtkbt_callbacks == NULL or onGenericEvent==NULL\n", id, event, data, len);

    return -1;
}
static void *rtkbt_api_getbuf (UINT16 size, const char* func, int line)
{
#ifdef BLUETOOTH_RTK_DBG_MEM
    return RTKBT_GKI_getbuf(size, func, line);
#else
    return osi_malloc(size);
#endif
}
static void rtkbt_api_freebuf (void * p)
{
    osi_free(p);
}
RTKBT_API_CALLBACK rtkbt_api_callbacks = {
    .version = RTKBT_API_VERSION,
    .size = sizeof(RTKBT_API_CALLBACK),
    .RegisterGenericCommand = rtkbt_api_RegisterGenericCommand,
    .RegisterPluginExMsg = rtkbt_api_RegisterPluginExMsg,
    .Send_PluginMsg = rtkbt_api_Send_PluginMsg,
    .SendGenericEvent = rtkbt_api_SendGenericEvent,
    .RegisterHook = rtkbt_api_RegisterHook,
    .GetConfig = rtkbt_api_GetConfig,
    .SetUipcPath = rtkbt_api_SetUipcPath,
    .plugin_getbuf = rtkbt_api_getbuf,
    .plugin_freebuf = rtkbt_api_freebuf,
    .UIPC_Send = UIPC_Send,
    .UIPC_Open = UIPC_Open,
    .UIPC_Close = UIPC_Close,
    .UIPC_Ioctl = UIPC_Ioctl,
    .UIPC_Read = UIPC_Read,
    .UIPC_Send_noblock = UIPC_Send_noblock,
    .bta_hh_le_write_rpt = bta_hh_le_write_rpt,
    .BTM_ReadInquiryRspTxPower = BTM_ReadInquiryRspTxPower,
    .BTM_RegisterForVSEvents = BTM_RegisterForVSEvents,
    .BTM_VendorSpecificCommand = BTM_VendorSpecificCommand,
    .BTM_SetDeviceClass = BTM_SetDeviceClass,
    .BTM_SetDiscoverability = BTM_SetDiscoverability,
    .BTM_ReadDeviceClass = BTM_ReadDeviceClass,
    .btm_ble_process_adv_pkt = btm_ble_process_adv_pkt,
    .bta_hh_le_find_dev_cb_by_bda = bta_hh_le_find_dev_cb_by_bda,
    .btif_storage_get_remote_device_property = btif_storage_get_remote_device_property,
    .BTA_HhSendData = BTA_HhSendData,
    .btsnd_hcic_write_ext_inquiry_response = btsnd_hcic_write_ext_inquiry_response,
    .BTA_GATTC_ConfigureMTU = BTA_GATTC_ConfigureMTU,
    .btm_sec_is_a_bonded_dev = btm_sec_is_a_bonded_dev,
    .btsnd_hcic_write_inqscan_type = btsnd_hcic_write_inqscan_type,
    .btsnd_hcic_write_pagescan_type = btsnd_hcic_write_pagescan_type,
    .btsnd_hcic_write_pagescan_cfg = btsnd_hcic_write_pagescan_cfg,
    .btsnd_hcic_write_scan_enable = btsnd_hcic_write_scan_enable,
};
/*
    loadplugins list in /system/etc/bluetooth/rtkbt_plugins.conf
    a sample of rtkbt_plugins.conf:

    test.so
    vr_iflytek.so
    vhid.so

*/
void loadplugins(RTKBT_API_CALLBACK * callback)
{
    char path[1024];
    char plugin[64];
    char * p;
    int i;
    void * handle;
    struct PLUGIN_INFO_ST * plugin_info = NULL;
    FILE * fp;
    RTKBT_API_INIT_ARG arg;

    fp = fopen(RTKBT_CONF, "r");
    if(!fp)
    {
        BTIF_TRACE_ERROR("fopen %s fail",RTKBT_CONF);
        return;
    }

    while(fgets(plugin, sizeof(plugin)-1, fp) != NULL)
    {
        for(i = (strlen(plugin)-1); ((plugin[i]==0x0d)||(plugin[i]==0x0a));i--)
        {
            plugin[i] = 0;
        }
        memset(path, 0 ,sizeof(path));
        p = strstr(plugin, ":");
        if(p)
        {
            arg.loglevel = atoi(p+1);
            *p = 0;
        }else
            arg.loglevel = 0;

        sprintf(path, "%s/rtkbt_plugin_%s.conf", RTKBT_CONF_DIR, plugin);
        BTIF_TRACE_DEBUG("loadconfig(%s) ... ", path);
        rtkbt_loadconfig(path);
        sprintf(path, "%s/%s.so", RTKBT_PLUGIN_DIR, plugin);
        BTIF_TRACE_DEBUG("loadplugins(%s) ... ", path);
        handle = dlopen(path, RTLD_NOW);
        if(!handle){
            BTIF_TRACE_ERROR("dlopen(%s) fail!", path);
            continue;
        }
        plugin_info = dlsym(handle, "PLUGIN_INFO");
        if(plugin_info)
        {
            if((plugin_info->version&0xffff0000) == (RTKBT_API_VERSION&0xffff0000)){
                BTIF_TRACE_API("loadplugin(%s) OK: Plugin Version(%08x) RTKBT_API_VERSION(%08x)", path, plugin_info->version, RTKBT_API_VERSION);
                plugin_info->init(callback, &arg);
            }else
                BTIF_TRACE_ERROR("loadplugin(%s) fail: Plugin Version(%08x) RTKBT_API_VERSION(%08x)", path, plugin_info->version, RTKBT_API_VERSION);
        }else
            BTIF_TRACE_ERROR("loadplugin(%s) fail:dlsym(PLUGIN_INFO) fail!", path);
    }
    if(fp)
        fclose(fp);

    return;
}

static bt_status_t init(rtkbt_callbacks_t* callbacks)
{
    BTIF_TRACE_API("%s RTKBT_API_VERSION: %08x", __FUNCTION__, RTKBT_API_VERSION);
    pthread_mutexattr_init(&rtkbt_mutexattr);
    pthread_mutex_init(&rtkbt_mutex, &rtkbt_mutexattr);
    stopServiceFlag = false;
    memset(rtkbt_GenericCommand_funcs, 0, sizeof(rtkbt_GenericCommand_funcs));
    memset(rtkbt_Hook_funcs, 0, sizeof(rtkbt_Hook_funcs));
    memset(rtkbt_UipcPath, 0, sizeof(rtkbt_UipcPath));
    rtkbt_conf_init();
    rtkbt_callbacks = callbacks;
    UIPC_Init(0);
    loadplugins(&rtkbt_api_callbacks);
    rtkbt_api_Hook(RTKBT_HOOK_ENABLE_BT_COMPLETE, (void *)BT_STATE_ON, 0);
    return BT_STATUS_SUCCESS;
}
static void cleanup()
{
    int i;
    BTIF_TRACE_API("%s", __FUNCTION__);
    pthread_mutex_lock(&rtkbt_mutex);
    rtkbt_conf_exit();
    memset(rtkbt_GenericCommand_funcs, 0, sizeof(rtkbt_GenericCommand_funcs));
    stopServiceFlag = true;
    for(i=0;i<UIPC_CH_NUM;i++)
    {
        if(rtkbt_UipcPath[i])
            free(rtkbt_UipcPath[i]);
    }
    memset(rtkbt_UipcPath, 0, sizeof(rtkbt_UipcPath));
    pthread_mutex_unlock(&rtkbt_mutex);
    return;
}

rtkbt_interface_t bt_rtkbt_interface = {
    .size = sizeof(rtkbt_interface_t),
    .init = init,
    .cleanup = cleanup,
    .GetFeature = rtkbt_GetFeature,
    .GenericCommand = rtkbt_GenericCommand,
};
const rtkbt_interface_t *btif_rtkbt_get_interface(void)
{
    BTIF_TRACE_API("%s", __FUNCTION__);
    return &bt_rtkbt_interface;
}

static future_t *start_up(void) {
  init(NULL);
  return NULL;
}

static future_t *shut_down(void) {
  cleanup();
  return NULL;
}

EXPORT_SYMBOL const module_t rtkbt_plugin_module = {
  .name = RTKBT_PLUGIN_MODULE,
  .init = NULL,
  .start_up = start_up,
  .shut_down = shut_down,
  .clean_up = NULL,
  .dependencies = {
    NULL,
    NULL
  }
};


#endif
