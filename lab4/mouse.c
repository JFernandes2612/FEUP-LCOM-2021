#include <stdint.h>
#include "mouse.h"

static int hook_id;

int (mouse_subscribe_int)(uint8_t *bit_no) {
  hook_id = *bit_no;
  sys_irqsetpolicy(IRQ_12, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id);
  return 0;
}

int (mouse_unsubscribe_int)() {
  sys_irqrmpolicy(&hook_id);
  return 0;
}

int (kbc_write_command)(uint8_t cmd) {
  uint8_t stat;
  while( 1 ) {
    util_sys_inb(KBC_ST_REG, &stat); /* assuming it returns OK */
    /* loop while 8042 input buffer is not empty */
    if( !(stat & KBC_ST_IBF) ) {
      sys_outb(KBC_CTRL_REG, cmd); /* no args command */
      return 0;
    }
    tickdelay(micros_to_ticks(DELAY_US)); // e.g. tickdelay()
  }
}

int (mouse_write_command)(uint8_t cmd) {
  uint8_t stat;
  uint8_t response = 0;
  kbc_write_command(KBC_WRITE_M);
  while(response != MOUSE_ACK) {
    util_sys_inb(KBC_ST_REG, &stat); // assuming it returns OK
    // loop while 8042 input buffer is not empty
    if( !(stat & KBC_ST_IBF) ) {
      sys_outb(KBC_IN_BUF, cmd); // no args command
      util_sys_inb(KBC_OUT_BUF, &response);
    }
    tickdelay(micros_to_ticks(DELAY_US)); // e.g. tickdelay()
  }
  return 0;
}
