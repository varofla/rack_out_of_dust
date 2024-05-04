#ifndef MAIN_MW_ZIGBEE_ZCL_ZB_ZCL_PM2_5_MEASUREMENT_ADDONS
#define MAIN_MW_ZIGBEE_ZCL_ZB_ZCL_PM2_5_MEASUREMENT_ADDONS

#include <zboss_api.h>

typedef struct {
  zb_uint16_t measured_value;
  zb_uint16_t min_measured_value;
  zb_uint16_t max_measured_value;
  zb_uint16_t tolerance;
} zb_zcl_pm2_5_measurement_attrs_t;

#endif /* MAIN_MW_ZIGBEE_ZCL_ZB_ZCL_PM2_5_MEASUREMENT_ADDONS */
