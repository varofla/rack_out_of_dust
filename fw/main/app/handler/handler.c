#include "handler.h"

#include "reset_button_handler/reset_button_handler.h"
#include "zigbee_fz_handler/zigbee_fz_handler.h"

bool handler_init(void) {
  int ret = true;

  ret &= reset_button_handler_init();
  ret &= zigbee_fz_handler_init();

  return ret;
}
