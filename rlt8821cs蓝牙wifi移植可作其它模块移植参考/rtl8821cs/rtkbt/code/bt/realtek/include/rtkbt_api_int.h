#include "rtkbt_api_ver.h"
#include "bta_gatt_api.h"
#include "bta_hh_api.h"
#include "bta_hh_int.h"
#include "uipc.h"
#include "bt_types.h"
#include "btm_api.h"
#include "btm_int.h"
#include "bta_api.h"
#include "hcimsgs.h"
#include "hcidefs.h"
#include "bta_dm_int.h"

#define RTKBT_API_VERSION   (SUBVER_RTKBT_TOOLCHAIN<<24|SUBVER_RTKBT_API<<16|SUBVER_RTKBT_REVISION<<8|SUBVER_RTKBT_CUSTOMIZED_REVISION)

#ifdef BLUETOOTH_RTK_DBG_MEM
extern void   *RTKBT_GKI_getbuf (UINT16, const char*, int);
#else
extern void   *GKI_getbuf (UINT16);
#endif

#define rtkbt_plugin_getbuf(x) plugin_getbuf((x), __FUNCTION__,__LINE__)
#define rtkbt_plugin_freebuf(x) plugin_freebuf((x))
extern void bta_hh_le_write_rpt(tBTA_HH_DEV_CB *p_cb,
                                 tBTA_HH_RPT_TYPE r_type,
                                                          BT_HDR *p_buf, UINT16 w4_evt );
extern tBTA_HH_DEV_CB * bta_hh_le_find_dev_cb_by_bda(BD_ADDR bda);
