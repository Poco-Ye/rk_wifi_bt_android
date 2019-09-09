#ifndef INCLUDE_RTKBT_API_H
#define INCLUDE_RTKBT_API_H
#include <ctype.h>
#include <string.h>
#include "bt_types.h"
#include "rtkbt_config.h"
#include "hardware/bluetooth.h"
#include "rtkbt_api_int.h"

#define RTKBT_TEST_ID               (0)
#define RTKBT_VHID_ID               (1)
#define RTKBT_AUTOPAIR_ID           (2)
#define RTKBT_VR_ID                 (3)
#define RTKBT_3DD_ID                (4)
#define RTKBT_HEARTBEAT_ID          (5)
#define RTKBT_HUAWEI_AUTOPAIR       (15)
#define RTKBT_MAX_ID                (16)

#define RTKBT_PLUGIN_BC             (0xFF)

#define RTKBT_PLUGIN_DIR "/system/lib/rtkbt"
#define RTKBT_CONF_DIR "/system/etc/bluetooth"
#define RTKBT_CONF RTKBT_CONF_DIR"/rtkbt_plugins.conf"

#define rtkbt_plugin_getbuf(x) plugin_getbuf((x), __FUNCTION__,__LINE__)
#define rtkbt_plugin_freebuf(x) plugin_freebuf((x))


static const char RTKBT_PLUGIN_MODULE[] = "rtkbt_plugin_module";

/*************************************************************************************
** plugin communicate each others with the args defined below
**tPlugin_comm will be added by each plugin
**
*************************************************************************************/
typedef struct
{
    tBTA_HH_DEV_CB * p_dev_cb;
}tVih_2_Vr_g_dev_cb;

//plugin communicate with each other, using different
typedef union
{
    tVih_2_Vr_g_dev_cb  vr_dev_cb;
}tPlugin_comm;

enum{
    VHID_2_VR_G_DEV_CB,
};

typedef int (* rtkbt_api_GenericCommand_func)(int id, int command, unsigned char * data, int len);
typedef int (* rtkbt_api_Hook_func)(int event, void * arg, int len);
typedef int (* rtkbt_api_Plugin_comm_func) (int id, int event, tPlugin_comm * plugin_arg);
typedef struct{
    int loglevel;
}RTKBT_API_INIT_ARG;

typedef struct{
    unsigned int version;
    int size;
    /*******************************************************************************
        **
        ** Function         RegisterGenericCommand
        **
        ** Description     GenericCommand call from JAVA to  bluedroid, rtkbt_api_RegisterGenericCommand is used by plugin to register a callback for recv GenericCommand.(used by plugin).
        ** Arguments      id: plugin id(RTKBT_AUTOPAIR_ID,RTKBT_VR_ID, etc.)
        **                      handler: callback
        ** Returns          0-success/other-fail
        **
        *******************************************************************************/
    int (*RegisterGenericCommand)(int id, rtkbt_api_GenericCommand_func handler);
    /*********************************************************************************
        **
        ** Function         RegisterPluginExMsg
        **
        ** Description     plugins need to communicate with each other for some reasons, register the func to rtkbt_api.c
        ** Arguments      id: plugin id(RTKBT_AUTOPAIR_ID,RTKBT_VR_ID, etc.)
        **                      handler: callback
        ** Returns          0-success/other-fail
        **
    *************************************************************************************/
    int (*RegisterPluginExMsg)(int id, rtkbt_api_Plugin_comm_func handler);
    /*******************************************************************************
        **
        ** Function        Send_PluginMsg
        **
        ** Description    send event to dest plugin
        ** Arguments    id: plugin id(RTKBT_AUTOPAIR_ID,RTKBT_VR_ID, etc.)
        **                     event: internal event by each plugin.
        **                     plugin_arg: data associated with event.
        ** Returns         BT_STATUS_SUCCESS/BT_STATUS_FAIL
        **
        *******************************************************************************/
    int (*Send_PluginMsg)(int id, int event, tPlugin_comm * plugin_arg);
    /*******************************************************************************
        **
        ** Function        SendGenericEvent
        **
        ** Description    send GenericEvent from bluedroid&plugin to JAVA.(used by bluedroid&plugin).
        ** Arguments    id: plugin id(RTKBT_AUTOPAIR_ID,RTKBT_VR_ID, etc.)
        **                     event: internal event by each plugin.
        **                     data: data associated with event.
        **                     len:  length of data associated with event.
        ** Returns         BT_STATUS_SUCCESS/BT_STATUS_FAIL
        **
        *******************************************************************************/
    int (*SendGenericEvent)(int id, int event, unsigned char * data, int len);
    /*******************************************************************************
        **
        ** Function         RegisterHook
        **
        ** Description     Register a callback to catch bluedroid Hooks.(used by plugin).
        ** Arguments      id: plugin id(RTKBT_AUTOPAIR_ID,RTKBT_VR_ID, etc.)
        **                      handler: callback
        ** Returns          0-success/other-fail
        **
        *******************************************************************************/
    int (*RegisterHook)(int id, rtkbt_api_Hook_func handler);
    /*******************************************************************************
        **
        ** Function         GetConfig
        **
        ** Description     Register a callback to get config.(used by plugin).
        ** Arguments      id: plugin id(RTKBT_AUTOPAIR_ID,RTKBT_VR_ID, etc.)
        **                      group: config group(NULL-Global Group)
        **                      item: config item(can't be NULL)
        ** Returns          NULL-not found /other-value
        **
        *******************************************************************************/
    char * (*GetConfig)(int id, char * group, char * item);
    /*******************************************************************************
        **
        ** Typedef         SetUipcPath
        **
        ** Description     plugin set Uipc path,rtkbt_api_SetUipcPath must be called before UIPC_Open(used by plugin).
        ** Arguments      ch_id: UIPC_CH_ID_RTKBT_CHANNEL_{1,2,3,4,5,6}
        ** Arguments      path: data path for ch_id
        ** Returns          0-success/other-fail
        **
        *******************************************************************************/
    int (*SetUipcPath)(int ch_id, char * path);

    void   *(*plugin_getbuf) (UINT16,const char*, int);
    void    (*plugin_freebuf) (void *);
    BOOLEAN (*UIPC_Open)(tUIPC_CH_ID ch_id, tUIPC_RCV_CBACK *p_cback);
    void (*UIPC_Close)(tUIPC_CH_ID ch_id);
    BOOLEAN (*UIPC_Ioctl)(tUIPC_CH_ID ch_id, UINT32 request, void *param);
    UINT32 (*UIPC_Read)(tUIPC_CH_ID ch_id, UINT16 *p_msg_evt, UINT8 *p_buf, UINT32 len);
    BOOLEAN (*UIPC_Send)(tUIPC_CH_ID ch_id, UINT16 msg_evt, UINT8 *p_buf, UINT16 msglen);
    INT32 (*UIPC_Send_noblock)(tUIPC_CH_ID ch_id, UINT16 msg_evt, UINT8 *p_buf, UINT16 msglen);
    void (*bta_hh_le_write_rpt)(tBTA_HH_DEV_CB *p_cb,tBTA_HH_RPT_TYPE r_type,BT_HDR *p_buf, UINT16 w4_evt );
    tBTM_STATUS (*BTM_ReadInquiryRspTxPower) (tBTM_CMPL_CB *p_cb);
    tBTM_STATUS (*BTM_RegisterForVSEvents) (tBTM_VS_EVT_CB *p_cb, BOOLEAN is_register);
    tBTM_STATUS (*BTM_VendorSpecificCommand)(UINT16 opcode, UINT8 param_len,
                                      UINT8 *p_param_buf, tBTM_VSC_CMPL_CB *p_cb);
    tBTM_STATUS (*BTM_SetDeviceClass) (DEV_CLASS cod);
    tBTM_STATUS (*BTM_SetDiscoverability) (UINT16 inq_mode, UINT16 window, UINT16 interval);
    UINT8 * (*BTM_ReadDeviceClass) (void);
    void (*btm_ble_process_adv_pkt) (UINT8 *p_data);
    tBTA_HH_DEV_CB* (*bta_hh_le_find_dev_cb_by_bda)(BD_ADDR bda);
    bt_status_t (*btif_storage_get_remote_device_property)(bt_bdaddr_t *remote_bd_addr,
                                                    bt_property_t *property);
    void (*BTA_HhSendData)(UINT8 dev_handle, BD_ADDR dev_bda, BT_HDR  *p_data);
    void (*bta_dm_set_eir_config) (tBTA_DM_MSG *p_data);
    BOOLEAN (*btsnd_hcic_set_reserved_lt_addr) (UINT8 lt_addr);
    BOOLEAN (*btsnd_hcic_write_sync_train_param) (UINT8* p_data);
    BOOLEAN (*btsnd_hcic_set_clb) (UINT8* p_data);
    BOOLEAN (*btsnd_hcic_start_sync_train) (void);
    BOOLEAN (*btsnd_hcic_write_clb_data) (UINT8* p_data, UINT8 len);
    void (*btsnd_hcic_write_ext_inquiry_response) (void *buffer, UINT8 fec_req);
    void (*BTA_GATTC_ConfigureMTU) (UINT16 conn_id, UINT16 mtu);
    BOOLEAN (*btm_sec_is_a_bonded_dev) (BD_ADDR bda);
    BOOLEAN (*btsnd_hcic_write_inqscan_type) (UINT8 type);
    BOOLEAN (*btsnd_hcic_write_pagescan_type) (UINT8 type);
    BOOLEAN (*btsnd_hcic_write_pagescan_cfg)(UINT16 interval,UINT16 window);
    BOOLEAN (*btsnd_hcic_write_scan_enable)(UINT8 flag);
}RTKBT_API_CALLBACK;
typedef int (* Rtkbt_Plugin_Init_func)(RTKBT_API_CALLBACK * callback, RTKBT_API_INIT_ARG * arg);

enum {
    RTKBT_HOOK_ENABLE_BT_BEGIN = 1,         // args: int    len:0
    RTKBT_HOOK_ENABLE_BT_COMPLETE,          // args: N/A    len:0
    RTKBT_HOOK_DISABLE_BT_BEGIN,            // args: N/A    len:0
    RTKBT_HOOK_DISABLE_BT_COMPLETE,         // args: int    len:0
    RTKBT_HOOK_HID_STATUS,                  // args: RTKBT_HOOK_HID_STATUS_ARG   len:sizeof(RTKBT_HOOK_HID_STATUS_ARG)
    RTKBT_HOOK_BLE_HH_NOTIY,                // args: RTKBT_HOOK_BLE_HH_NOTIY_ARG   len:sizeof(RTKBT_HOOK_BLE_HH_NOTIY_ARG)
    RTKBT_HOOK_AUTOPAIR_VND_EVENT,          // args: NULL   len:0
    RTKBT_HOOK_LE_HID_WHITE_LIST_STATUS,    // args: RTKBT_HOOK_HID_STATUS_ARG   len:sizeof(RTKBT_HOOK_HID_STATUS_ARG)
    RTKBT_HOOK_RECEIVE_HCI_VENDOR_EVENT,               // args: BT_HDR*    len:0
    RTKBT_HOOK_HH_LE_OPEN_CMPL,             // args: tBTA_HH_DEV_CB *   len: sizeof(tBTA_HH_DEV_CB)
    RTKBT_HOOK_GATTC_CFG_MTU_EVT,           // args: tBTA_GATTC_CFG_MTU* len: sizeof(tBTA_GATTC_CFG_MTU)
    RTKBT_HOOK_HEARTBEAT_EVENT_COMPLETE,
};
typedef struct{
    int status;
    bt_bdaddr_t * addr;
}RTKBT_HOOK_HID_STATUS_ARG;
#include "bta_hh_int.h"
#include "bta_dm_int.h"
#include "bta_gatt_api.h"
typedef struct{
    tBTA_HH_DEV_CB* p_dev_cb;
    tBTA_HH_LE_RPT* p_rpt;
    tBTA_GATTC_NOTIFY *p_data;
}RTKBT_HOOK_BLE_HH_NOTIY_ARG;
typedef struct{
    BOOLEAN         add_or_remv;
    tBTM_SEC_DEV_REC* p_dev_rec;
}RTKBT_HOOK_LE_HID_STATUS_ARG;


/*******************************************************************************
**
** Function         rtkbt_api_Hook
**
** Description     call Hooks(used by bluedroid).
** Arguments      status: 1-connected / 0-disconnected
**                      addr: HID device's address
** Returns          0-success/other-fail
**
*******************************************************************************/
extern int rtkbt_api_Hook(int event, void * arg, int len);

/*******************************************************************************
**
** Typedef         rtkbt_api_GetUipcPath
**
** Description     When UIPC_Open called, Uipc get DataPath by call rtkbt_api_GetUipcPath(used by bluedroid).
** Arguments      ch_id: UIPC_CH_ID_RTKBT_CHANNEL_{1,2,3,4,5,6}
** Returns          data path
**
*******************************************************************************/
extern char * rtkbt_api_GetUipcPath(int ch_id);
extern char * rtkbt_api_GetConfig(int id, char * group, char * item);


static inline int rtkbt_api_NotifyHIDStatus(int status, bt_bdaddr_t* addr)
{
    RTKBT_HOOK_HID_STATUS_ARG arg;
    arg.status = status;
    arg.addr = addr;
    return rtkbt_api_Hook(RTKBT_HOOK_HID_STATUS, &arg, sizeof(arg));
}
static inline int rtkbt_api_BleHHNotify(tBTA_HH_DEV_CB* p_dev_cb, tBTA_HH_LE_RPT* p_rpt, tBTA_GATTC_NOTIFY *p_data)
{
    RTKBT_HOOK_BLE_HH_NOTIY_ARG arg;
    arg.p_dev_cb = p_dev_cb;
    arg.p_rpt = p_rpt;
    arg.p_data = p_data;
    return rtkbt_api_Hook(RTKBT_HOOK_BLE_HH_NOTIY, &arg, sizeof(arg));
}

static inline int rtkbt_api_NotifyLeHIDWhitelistStatus(int to_add, tBTM_SEC_DEV_REC* p_dev_rec)
{
    RTKBT_HOOK_LE_HID_STATUS_ARG arg;
    arg.add_or_remv = to_add;
    arg.p_dev_rec = p_dev_rec;
    return rtkbt_api_Hook(RTKBT_HOOK_LE_HID_WHITE_LIST_STATUS, &arg, sizeof(arg));
}

#define rtkbt_api_XDIGIT2INT(x)   (((x)>='a')?((x)-'a'+10):(((x)>='A')?((x)-'A'+10):((x)-'0')))
static inline int rtkbt_api_str2hex(char * str, UINT8 * hex, int *len)
{
    int i,size;

    size = strlen(str);
    if(size%2)
    {
        *len = 0;
        return -1;
    }
    for(i=0; i< size;i+=2)
    {
        if(isxdigit(str[i])&&isxdigit(str[i+1]))
            hex[i>>1] = (rtkbt_api_XDIGIT2INT(str[i])<<4)|rtkbt_api_XDIGIT2INT(str[i+1]);
        else
            return -2;
    }
    *len = i>>1;
    return 0;
}


struct PLUGIN_INFO_ST{
    unsigned int version;
    Rtkbt_Plugin_Init_func init;
};

#define PLUGIN_INIT(func) \
   EXPORT_SYMBOL struct PLUGIN_INFO_ST  PLUGIN_INFO = \
    {   \
        .version = RTKBT_API_VERSION, \
        .init = (func) \
    }
#endif
