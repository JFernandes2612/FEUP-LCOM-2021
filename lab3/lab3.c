#include <lcom/lcf.h>

#include <lcom/lab3.h>

#include <stdbool.h>
#include <stdint.h>
#include "i8042.h"
#include "kbd.h"

#define LAB3TEST

static bool read_error = false;
static uint8_t data = 0;

#ifdef LAB3TEST
static uint32_t count = 0;
#endif

int main(int argc, char *argv[])
{
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

void(kbc_ih)(void)
{
  uint8_t stat;
  while (1)
  {
    util_sys_inb(KBC_ST_REG, &stat); /* assuming it returns OK */
#ifdef LAB3TEST
    count++;
#endif
    /* loop while 8042 output buffer is empty */
    if (stat & KBC_OBF)
    {
      util_sys_inb(KBC_OUT_BUF, &data); /* ass. it returns OK */
#ifdef LAB3TEST
      count++;
#endif
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
    //tickdelay(micros_to_ticks(DELAY_US)); // e.g. tickdelay()
  }
}

int(kbd_test_scan)()
{
  int ipc_status;
  message msg;
  uint8_t bit_no = 0;
  kbd_subscribe_int(&bit_no);
  int irq_set = BIT(bit_no);
  bool make;
  uint8_t bytes[2];
  bool double_byte = false;
  while (data != (ESC | BREAKC))
  { /* You may want to use a different condition */
    /* Get a request message. */
    if ((driver_receive(ANY, &msg, &ipc_status)) != 0)
    {
      continue;
    }
    if (is_ipc_notify(ipc_status))
    { /* received notification */
      switch (_ENDPOINT_P(msg.m_source))
      {
      case HARDWARE: /* hardware interrupt notification */
        if (msg.m_notify.interrupts & irq_set)
        { /* subscribed interrupt */
          kbc_ih();
          if (!read_error)
          {
            make = !(data & BREAKC);
            if (double_byte)
            {
              bytes[1] = data;
#ifdef LAB3TEST
              kbd_print_scancode(make, 2, bytes);
#endif
              double_byte = false;
            }
            else
            {
              bytes[0] = data;
              if ((uint8_t)data == TWO_BYTE_SC)
                double_byte = true;
              else
              {
#ifdef LAB3TEST
                kbd_print_scancode(make, 1, bytes);
#endif
              }
            }
          }
        }
        break;
      default:
        break; /* no other notifications expected: do nothing */
      }
    }
    else
    { /* received a standard message, not a notification */
      /* no standard messages expected: do nothing */
    }
  }
  kbd_unsubscribe_int();
#ifdef LAB3TEST
  return kbd_print_no_sysinb(count);
#endif
  return 0;
}

int(kbd_test_poll)()
{
  bool make;
  uint8_t bytes[2];
  bool double_byte = false;
  uint8_t final_cmd;
  kbd_write_command(KBC_READ);
  util_sys_inb(KBC_OUT_BUF, &final_cmd);
  while (data != (ESC | BREAKC))
  {
    kbc_ih();
    if (!read_error)
    {
      make = !(data & BREAKC);
      if (double_byte)
      {
        bytes[1] = data;
#ifdef LAB3TEST
        kbd_print_scancode(make, 2, bytes);
#endif
        double_byte = false;
      }
      else
      {
        bytes[0] = data;
        if ((uint8_t)data == TWO_BYTE_SC)
          double_byte = true;
        else
        {
#ifdef LAB3TEST
          kbd_print_scancode(make, 1, bytes);
#endif
        }
      }
    }
  }
  kbd_write_command(KBC_WRITE);
  sys_outb(KBC_OUT_BUF, final_cmd | KBC_CMB_ENI_K);
  return 0;
}

int(kbd_test_timed_scan)(uint8_t idle)
{
  /* To be completed by the students
  printf("%s is not yet implemented!\n", __func__); */
  int ipc_status;
  message msg;
  uint8_t bit_no = 0;
  kbd_subscribe_int(&bit_no);
  int kbd_int_bit = BIT(bit_no);
  bit_no = 1;
  timer_subscribe_int(&bit_no);
  int timer0_int_bit = BIT(bit_no);
  bool make;
  uint8_t bytes[2];
  bool double_byte = false;
  int elapsed_ticks = 0;
  bool ended_time = false;
  while (data != (ESC | BREAKC) && !ended_time)
  { /* You may want to use a different condition */
    /* Get a request message. */
    if ((driver_receive(ANY, &msg, &ipc_status)) != 0)
    {
      continue;
    }
    if (is_ipc_notify(ipc_status))
    { /* received notification */
      switch (_ENDPOINT_P(msg.m_source))
      {
      case HARDWARE: /* hardware interrupt notification */
        if (msg.m_notify.interrupts & kbd_int_bit)
        { /* subscribed keyboard interrupt */
          kbc_ih();
          if (!read_error)
          {
            make = !(data & BREAKC);
            if (double_byte)
            {
              bytes[1] = data;
#ifdef LAB3TEST
              kbd_print_scancode(make, 2, bytes);
#endif
              double_byte = false;
            }
            else
            {
              bytes[0] = data;
              elapsed_ticks = 0;
              if (data == TWO_BYTE_SC)
                double_byte = true;
              else
              {
#ifdef LAB3TEST
                kbd_print_scancode(make, 1, bytes);
#endif
              }
            }
          }
        }
        if(msg.m_notify.interrupts & timer0_int_bit)
        {
          elapsed_ticks++;
          if (elapsed_ticks == idle*60){
            ended_time = true;
          }
        }
        break;
      default:
        break; /* no other notifications expected: do nothing */
      }
    }
    else
    { /* received a standard message, not a notification */
      /* no standard messages expected: do nothing */
    }
  }
  kbd_unsubscribe_int();
  timer_unsubscribe_int();
#ifdef LAB3TEST
  return kbd_print_no_sysinb(count);
#endif
  return 0;
}
