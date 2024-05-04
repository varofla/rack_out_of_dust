#include "zboss_api.h"

#include "zb_zcl_pm2_5_measurement.h"

zb_ret_t check_value_pm2_5_measurement_server(zb_uint16_t attr_id, zb_uint8_t endpoint, zb_uint8_t *value);
void zb_zcl_pm2_5_measurement_write_attr_hook_server(zb_uint8_t endpoint, zb_uint16_t attr_id, zb_uint8_t *new_value);

void zb_zcl_pm2_5_measurement_init_server() {
  zb_zcl_add_cluster_handlers(ZB_ZCL_CLUSTER_ID_PM2_5_MEASUREMENT,
                              ZB_ZCL_CLUSTER_SERVER_ROLE,
                              check_value_pm2_5_measurement_server,
                              zb_zcl_pm2_5_measurement_write_attr_hook_server,
                              (zb_zcl_cluster_handler_t)NULL);
}

void zb_zcl_pm2_5_measurement_init_client() {
  zb_zcl_add_cluster_handlers(ZB_ZCL_CLUSTER_ID_PM2_5_MEASUREMENT,
                              ZB_ZCL_CLUSTER_CLIENT_ROLE,
                              (zb_zcl_cluster_check_value_t)NULL,
                              (zb_zcl_cluster_write_attr_hook_t)NULL,
                              (zb_zcl_cluster_handler_t)NULL);
}

zb_ret_t check_value_pm2_5_measurement_server(zb_uint16_t attr_id, zb_uint8_t endpoint, zb_uint8_t *value) {
  zb_ret_t ret = RET_OK;
  zb_int16_t val = ZB_ZCL_ATTR_GETS16(value);

  TRACE_MSG(TRACE_ZCL1, "> check_value_pm2_5_measurement, attr_id %d, val %d",
            (FMT__D_D, attr_id, val));

  // TODO: add checking

  TRACE_MSG(TRACE_ZCL1, "< check_value_pm2_5_measurement ret %hd", (FMT__H, ret));
  return ret;
}

void zb_zcl_pm2_5_measurement_write_attr_hook_server(
    zb_uint8_t endpoint, zb_uint16_t attr_id, zb_uint8_t *new_value) {
  ZVUNUSED(new_value);
  ZVUNUSED(endpoint);

  TRACE_MSG(TRACE_ZCL1, ">> zb_zcl_pm2_5_measurement_write_attr_hook endpoint %hd, attr_id %d",
            (FMT__H_D, endpoint, attr_id));

  /* All attributes in this cluster are read-only. Do nothing */

  TRACE_MSG(TRACE_ZCL1, "<< zb_zcl_pm2_5_measurement_write_attr_hook", (FMT__0));
}
