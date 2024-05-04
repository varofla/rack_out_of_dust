#ifndef MAIN_HW_DRIVER_FAN4P_FAN4P
#define MAIN_HW_DRIVER_FAN4P_FAN4P

#include <stdbool.h>
#include <stdint.h>

bool fan4p_init(void);

bool fan4p_set_power(uint8_t power);
uint16_t fan4p_get_rpm(void);

#endif /* MAIN_HW_DRIVER_FAN4P_FAN4P */
