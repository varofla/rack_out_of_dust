#include "mw.h"
#include "zigbee/zigbee.h"

bool mw_init(void) {
  bool ret = true;

  ret &= zigbee_init_();

  return ret;
}