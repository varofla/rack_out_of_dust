#ifndef MAIN_MW_ZIGBEE_ZCL_ZB_ZCL_MULTISTATE_OUTPUT
#define MAIN_MW_ZIGBEE_ZCL_ZB_ZCL_MULTISTATE_OUTPUT

#include "zcl/zb_zcl_common.h"

#include "zcl/zb_zcl_commands.h"

#define ZB_ZCL_CLUSTER_ID_MULTISTATE_OUTPUT 0x0013

/*! @brief Dust Measurement cluster attribute identifiers
    @see None ZCL spec.
*/
enum zb_zcl_multistate_output_attr_e {
  ZB_ZCL_ATTR_MULTISTATE_OUTPUT_NUMBER_OF_STATES_ID = 0x004A,
  ZB_ZCL_ATTR_MULTISTATE_OUTPUT_OUT_OF_SERVICE_ID = 0x0051,
  ZB_ZCL_ATTR_MULTISTATE_OUTPUT_PRESENT_VALUE_ID = 0x0055,
  ZB_ZCL_ATTR_MULTISTATE_OUTPUT_STATUS_FLAG_ID = 0x006F,
};

#define ZB_ZCL_MULTISTATE_OUTPUT_CLUSTER_REVISION_DEFAULT ((zb_uint16_t)0x00001)

#define ZB_SET_ATTR_DESCR_WITH_ZB_ZCL_ATTR_MULTISTATE_OUTPUT_NUMBER_OF_STATES_ID(data_ptr) \
  {                                                                                        \
    ZB_ZCL_ATTR_MULTISTATE_OUTPUT_NUMBER_OF_STATES_ID,                                     \
        ZB_ZCL_ATTR_TYPE_U16,                                                              \
        ZB_ZCL_ATTR_ACCESS_READ_ONLY,                                                      \
        (void *)data_ptr                                                                   \
  }

#define ZB_SET_ATTR_DESCR_WITH_ZB_ZCL_ATTR_MULTISTATE_OUTPUT_OUT_OF_SERVICE_ID(data_ptr) \
  {                                                                                      \
    ZB_ZCL_ATTR_MULTISTATE_OUTPUT_OUT_OF_SERVICE_ID,                                     \
        ZB_ZCL_ATTR_TYPE_U16,                                                            \
        ZB_ZCL_ATTR_ACCESS_READ_ONLY,                                                    \
        (void *)data_ptr                                                                 \
  }

#define ZB_SET_ATTR_DESCR_WITH_ZB_ZCL_ATTR_MULTISTATE_OUTPUT_PRESENT_VALUE_ID(data_ptr) \
  {                                                                                     \
    ZB_ZCL_ATTR_MULTISTATE_OUTPUT_PRESENT_VALUE_ID,                                     \
        ZB_ZCL_ATTR_TYPE_U16,                                                           \
        ZB_ZCL_ATTR_ACCESS_READ_ONLY | ZB_ZCL_ATTR_ACCESS_REPORTING,                    \
        (void *)data_ptr                                                                \
  }

#define ZB_SET_ATTR_DESCR_WITH_ZB_ZCL_ATTR_MULTISTATE_OUTPUT_STATUS_FLAG_ID(data_ptr) \
  {                                                                                   \
    ZB_ZCL_ATTR_MULTISTATE_OUTPUT_STATUS_FLAG_ID,                                     \
        ZB_ZCL_ATTR_TYPE_U16,                                                         \
        ZB_ZCL_ATTR_ACCESS_READ_ONLY | ZB_ZCL_ATTR_ACCESS_REPORTING,                  \
        (void *)data_ptr                                                              \
  }

/*! @internal Number of attributes mandatory for reporting in Dust Measurement cluster */
#define ZB_ZCL_MULTISTATE_OUTPUT_REPORT_ATTR_COUNT 2

/*! Write attribute hook is used to set min/max Dust values */
void zb_zcl_multistate_output_write_attr_hook(
    zb_uint8_t endpoint, zb_uint16_t attr_id, zb_uint8_t *new_value);

#define ZB_ZCL_DECLARE_MULTISTATE_OUTPUT_ATTRIB_LIST(attr_list,                                                    \
                                                     number_of_states, out_of_service, present_value, status_flag) \
  ZB_ZCL_START_DECLARE_ATTRIB_LIST_CLUSTER_REVISION(attr_list, ZB_ZCL_MULTISTATE_OUTPUT)                           \
  ZB_ZCL_SET_ATTR_DESC(ZB_ZCL_ATTR_MULTISTATE_OUTPUT_NUMBER_OF_STATES_ID, (number_of_states))                      \
  ZB_ZCL_SET_ATTR_DESC(ZB_ZCL_ATTR_MULTISTATE_OUTPUT_OUT_OF_SERVICE_ID, (out_of_service))                          \
  ZB_ZCL_SET_ATTR_DESC(ZB_ZCL_ATTR_MULTISTATE_OUTPUT_PRESENT_VALUE_ID, (present_value))                            \
  ZB_ZCL_SET_ATTR_DESC(ZB_ZCL_ATTR_MULTISTATE_OUTPUT_STATUS_FLAG_ID, (status_flag))                                \
  ZB_ZCL_FINISH_DECLARE_ATTRIB_LIST

void zb_zcl_multistate_output_init_server(void);
void zb_zcl_multistate_output_init_client(void);
#define ZB_ZCL_CLUSTER_ID_MULTISTATE_OUTPUT_SERVER_ROLE_INIT zb_zcl_multistate_output_init_server
#define ZB_ZCL_CLUSTER_ID_MULTISTATE_OUTPUT_CLIENT_ROLE_INIT zb_zcl_multistate_output_init_client

#endif /* MAIN_MW_ZIGBEE_ZCL_ZB_ZCL_MULTISTATE_OUTPUT */
