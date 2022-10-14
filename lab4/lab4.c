// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

#include <lcom/lab4.h>

// Any header files included below this line should have been created by you

#include "i8042.h"
#include "mouse.h"

static bool read_error = false;
static uint8_t data = 0;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab4/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}


void (mouse_ih) (void) {
  uint8_t stat;
  while (1)
  {
    util_sys_inb(KBC_ST_REG, &stat); /* assuming it returns OK */
    /* loop while 8042 output buffer is empty */
    if (stat & KBC_OBF)
    {
      util_sys_inb(KBC_OUT_BUF, &data); /* ass. it returns OK */
      if ((stat & (KBC_PAR_ERR | KBC_TO_ERR)) == 0)
      {
        read_error = false;
      }
      else
      {
        read_error = true;
      }
      break;
    }
    tickdelay(micros_to_ticks(DELAY_US));
  }
}

int (mouse_test_packet)(uint32_t cnt) {
  uint8_t bit_no = 0;
  mouse_subscribe_int(&bit_no);
  mouse_write_command(MOUSE_STREAM);
  mouse_write_command(MOUSE_EN_DATA_REP);
  int irq_set = BIT(bit_no);
  int ipc_status;
  message msg;
  struct packet curr_pack;
  uint8_t curr_byte = 0;
  while(cnt) {
    if ( (driver_receive(ANY, &msg, &ipc_status)) != 0 ) { /* Get a request message. */
      continue;
    }
    if (is_ipc_notify(ipc_status)) { /* received notification */
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: /* hardware interrupt notification */
          if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */
            mouse_ih();
            if(read_error) {
              continue;
            }
            curr_pack.bytes[curr_byte] = data;
            switch (curr_byte) {
              case 0:
                curr_pack.y_ov = data & BIT(7);
                curr_pack.x_ov = data & BIT(6);
                curr_pack.delta_y = (data & BIT(5)) << 9;
                curr_pack.delta_x = (data & BIT(4)) << 9;
                curr_pack.mb = data & BIT(2);
                curr_pack.rb = data & BIT(1);
                curr_pack.lb = data & BIT(0);
                curr_byte++;
                break;
              case 1:
                curr_pack.delta_x |= curr_pack.delta_x ? (data - 256) : data;
                curr_byte++;
                break;
              case 2:
                curr_pack.delta_y |= curr_pack.delta_y ? (data - 256) : data;
                mouse_print_packet(&curr_pack);
                cnt--;
                curr_byte = 0;
                break;
            }
          }
          break;
        default:
          break; /* no other notifications expected: do nothing */
      }
    } else { /* received a standard message, not a notification */
      /* no standard messages expected: do nothing */
    }
  }
  mouse_write_command(MOUSE_DIS_DATA_REP);
  mouse_unsubscribe_int();
  return 0;
}

int (mouse_test_async)(uint8_t idle_time) {
    /* To be completed */
    printf("%s(%u): under construction\n", __func__, idle_time);
    return 1;
}

int (mouse_test_gesture)(uint8_t x_len, uint8_t tolerance) {
    /* To be completed */
    printf("%s: under construction\n", __func__);
    return 1;
}

int (mouse_test_remote)(uint16_t period, uint8_t cnt) {
    /* To be completed */
    printf("%s(%u, %u): under construction\n", __func__, period, cnt);
    return 1;
}
