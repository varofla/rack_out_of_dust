#include "task.h"

#include "main_thread/main_thread.h"

bool task_init(void) {
  bool ret = true;

  ret &= main_thread_init();

  return ret;
}
