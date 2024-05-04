#ifndef MAIN_HW_DRIVER_STLED_STLED
#define MAIN_HW_DRIVER_STLED_STLED

#include <stdbool.h>

typedef enum {
  STLED_PATTERN_OFF = 0,
  STLED_PATTERN_ON = 1,

  STLED_PATTERN_BLINK_SLOW,
  STLED_PATTERN_BLINK_MEDIUM,
  STLED_PATTERN_BLINK_FAST,

  STLED_PATTERN_BREATH_SLOW,
  STLED_PATTERN_BREATH_MEDIUM,
  STLED_PATTERN_BREATH_FAST,
} stled_pattern_t;

bool stled_init(void);

bool stled_set(stled_pattern_t pattern);

#endif /* MAIN_HW_DRIVER_STLED_STLED */
