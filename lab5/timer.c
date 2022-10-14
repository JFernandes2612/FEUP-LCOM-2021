#include "time.h"
#include <lcom/lcf.h>

static int hook_id;

int (timer_subscribe_int)(uint8_t *bit_no) {
  hook_id = *bit_no;
  sys_irqsetpolicy(0x00, IRQ_REENABLE, &hook_id);
  return 0;
}

int (timer_unsubscribe_int)() {
  sys_irqrmpolicy(&hook_id);
  return 0;
}
