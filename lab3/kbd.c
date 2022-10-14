#include <lcom/lcf.h>

#include <stdint.h>
#include "kbd.h"
#include "i8042.h"

static int hook_id;
static int hook_id_timer;

int (kbd_subscribe_int)(uint8_t *bit_no) {
  hook_id = *bit_no;
  sys_irqsetpolicy(IRQ_1, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id);
  return 0;
}

int (kbd_unsubscribe_int)() {
  sys_irqrmpolicy(&hook_id);
  return 0;
}

int (kbd_write_command)(uint8_t cmd) {
  uint8_t stat;
  while( 1 ) {
    util_sys_inb(KBC_ST_REG, &stat); /* assuming it returns OK */
    /* loop while 8042 input buffer is not empty */
    if( !(stat & KBC_ST_IBF) ) {
      sys_outb(KBC_ST_REG, cmd); /* no args command */
      return 0;
    }
  tickdelay(micros_to_ticks(DELAY_US)); // e.g. tickdelay()
  }
}

int (timer_subscribe_int)(uint8_t *bit_no) {
  hook_id_timer = *bit_no;
  sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id_timer);
  return 0;
}

int (timer_unsubscribe_int)() {
  sys_irqrmpolicy(&hook_id_timer);
  return 0;
}
