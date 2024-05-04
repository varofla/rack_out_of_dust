#ifndef MAIN_HW_DRIVER_ZBRETBTN_ZBRSTBTN
#define MAIN_HW_DRIVER_ZBRETBTN_ZBRSTBTN

#include <stdbool.h>

typedef void (*zbrstbtn_callback_t)(uint8_t clicked_time);

bool zbrstbtn_init(void);

void zbrstbtn_set_callback(zbrstbtn_callback_t handler);

#endif /* MAIN_HW_DRIVER_ZBRETBTN_ZBRSTBTN */
