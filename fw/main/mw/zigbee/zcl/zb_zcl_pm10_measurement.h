#ifndef MAIN_MW_ZIGBEE_ZCL_ZB_ZCL_PM10_MEASUREMENT
#define MAIN_MW_ZIGBEE_ZCL_ZB_ZCL_PM10_MEASUREMENT

#include "zcl/zb_zcl_common.h"

#include "zcl/zb_zcl_commands.h"

#define ZB_ZCL_CLUSTER_ID_PM10_MEASUREMENT 0xfc81

/*! @brief Dust Measurement cluster attribute identifiers
    @see None ZCL spec.
*/
enum zb_zcl_pm10_measurement_attr_e {
  ZB_ZCL_ATTR_PM10_MEASUREMENT_MEASURED_VALUE_ID = 0xf003, /*!< MeasuredValue attribute */
};

#define ZB_ZCL_PM10_MEASUREMENT_CLUSTER_REVISION_DEFAULT ((zb_uint16_t)0x00002)

/** @brief Default value for MeasuredValue attribute */
#define ZB_ZCL_PM10_MEASUREMENT_MEASURED_VALUE_DEFAULT_VALUE (.0 / .0)

/** @brief MeasuredValue attribute unknown */
#define ZB_ZCL_PM10_MEASUREMENT_MEASURED_VALUE_UNKNOWN (.0 / .0)

/** @brief MaxMeasuredValue attribute maximum value */
// #define ZB_ZCL_PM10_MEASUREMENT_MAX_MEASURED_VALUE_MAX_VALUE 1.0

#define ZB_SET_ATTR_DESCR_WITH_ZB_ZCL_ATTR_PM10_MEASUREMENT_MEASURED_VALUE_ID(data_ptr) \
  {                                                                                     \
    ZB_ZCL_ATTR_PM10_MEASUREMENT_MEASURED_VALUE_ID,                                     \
        ZB_ZCL_ATTR_TYPE_U16,                                                           \
        ZB_ZCL_ATTR_ACCESS_READ_ONLY | ZB_ZCL_ATTR_ACCESS_REPORTING,                    \
        (void *)data_ptr                                                                \
  }

/*! @internal Number of attributes mandatory for reporting in Dust Measurement cluster */
#define ZB_ZCL_PM10_MEASUREMENT_REPORT_ATTR_COUNT 1

/*! Write attribute hook is used to set min/max Dust values */
void zb_zcl_pm10_measurement_write_attr_hook(
    zb_uint8_t endpoint, zb_uint16_t attr_id, zb_uint8_t *new_value);

/** @brief Declare attribute list for Dust Measurement cluster - server side
    @param attr_list - attribute list name
    @param measured_value - pointer to variable to store MeasuredValue attribute
    @param min_value - pointer to variable to store MinMeasuredValue attribute
    @param max_value - pointer to variable to store MAxMeasuredValue attribute
    @param tolerance - pointer to variable to store Tolerance attribute
*/
#define ZB_ZCL_DECLARE_PM10_MEASUREMENT_ATTRIB_LIST(attr_list,                           \
                                                    measured_value)                      \
  ZB_ZCL_START_DECLARE_ATTRIB_LIST_CLUSTER_REVISION(attr_list, ZB_ZCL_PM10_MEASUREMENT)  \
  ZB_ZCL_SET_ATTR_DESC(ZB_ZCL_ATTR_PM10_MEASUREMENT_MEASURED_VALUE_ID, (measured_value)) \
  ZB_ZCL_FINISH_DECLARE_ATTRIB_LIST

void zb_zcl_pm10_measurement_init_server(void);
void zb_zcl_pm10_measurement_init_client(void);
#define ZB_ZCL_CLUSTER_ID_PM10_MEASUREMENT_SERVER_ROLE_INIT zb_zcl_pm10_measurement_init_server
#define ZB_ZCL_CLUSTER_ID_PM10_MEASUREMENT_CLIENT_ROLE_INIT zb_zcl_pm10_measurement_init_client

#endif /* MAIN_MW_ZIGBEE_ZCL_ZB_ZCL_PM10_MEASUREMENT */
