#include "timer.h"
#include "i8254.h"

static int timer_hook_id;

int(timer_subscribe_int)(uint8_t *bit_no)
{
  timer_hook_id = *bit_no;
  if (sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &timer_hook_id))
    return 1;
  return 0;
}

int(timer_unsubscribe_int)()
{
  if (sys_irqrmpolicy(&timer_hook_id))
    return 1;
  return 0;
}
