#ifndef MAIN_MW_ZIGBEE_ZCL_ZB_ZCL_REL_HUMIDITY_MEASUREMENT_ADDONS
#define MAIN_MW_ZIGBEE_ZCL_ZB_ZCL_REL_HUMIDITY_MEASUREMENT_ADDONS

#include <zboss_api.h>

typedef struct {
  zb_uint16_t measure_value;
  zb_uint16_t min_measure_value;
  zb_uint16_t max_measure_value;
} zb_zcl_rel_humidity_measurement_attrs_t;

#endif /* MAIN_MW_ZIGBEE_ZCL_ZB_ZCL_REL_HUMIDITY_MEASUREMENT_ADDONS */
