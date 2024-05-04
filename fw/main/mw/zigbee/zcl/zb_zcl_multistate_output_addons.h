#ifndef MAIN_MW_ZIGBEE_ZCL_ZB_ZCL_MULTISTATE_OUTPUT_ADDONS
#define MAIN_MW_ZIGBEE_ZCL_ZB_ZCL_MULTISTATE_OUTPUT_ADDONS

#include <zboss_api.h>

typedef struct {
  zb_uint16_t number_of_states;
  zb_bool_t out_of_service;
  zb_uint16_t present_value;
  zb_uint8_t status_flags;
} zb_zcl_multistate_output_attrs_t;

#endif /* MAIN_MW_ZIGBEE_ZCL_ZB_ZCL_MULTISTATE_OUTPUT_ADDONS */
