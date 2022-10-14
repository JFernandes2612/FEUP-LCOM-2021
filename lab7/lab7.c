// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>
// Any header files included below this line should have been created by you

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab7/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab7/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

static int uart_com1_hook_id;

#define UART_COM1_BASE_ADDR 0x3F8

#define UART_DLL 0
#define UART_DLM 1

#define UART_RBR 0
#define UART_THR 0
#define UART_IER 1
#define UART_IIR 2
#define UART_FCR 2
#define UART_LCR 3
#define UART_MCR 4
#define UART_LSR 5
#define UART_MSR 6
#define UART_SR 7

#define UART_INT_NOT_PEND BIT(0)
#define UART_INT_ID ( BIT(1) | BIT(2) | BIT(3) )

#define UART_RDA_INT BIT(2)
#define UART_THRE_INT BIT(1)

#define UART_LSR_RECEIVER BIT(0)
#define UART_LSR_OVERRUN BIT(1)
#define UART_LSR_PARITY BIT(2)
#define UART_LSR_FRAME BIT(3)
#define UART_LSR_FIFO BIT(7)

static bool uart_read_error;
static bool uart_can_send = false;


int (util_sys_inb)(int port, uint8_t *value) {
  uint32_t val = 0;
  sys_inb(port, &val);
  *value = (uint8_t) val;
  return 0;
}

void uart_ih()
{
  uint8_t iir;
  util_sys_inb(UART_COM1_BASE_ADDR + UART_IIR, &iir);
  if (!(iir & UART_INT_NOT_PEND))
  {
    switch (iir & UART_INT_ID)
    {
      case UART_RDA_INT:
        {
            /* read received character */
            uint8_t uart_lsr_data;
            util_sys_inb(UART_COM1_BASE_ADDR + UART_LSR, &uart_lsr_data);
            while(uart_lsr_data & UART_LSR_RECEIVER)
            {
              uint8_t data;
              util_sys_inb(UART_COM1_BASE_ADDR + UART_RBR, &data);
              uart_read_error = uart_lsr_data & UART_LSR_FIFO;
              if(uart_read_error)
                printf("ufe\n");
              else printf("%c", data);
              util_sys_inb(UART_COM1_BASE_ADDR + UART_LSR, &uart_lsr_data);
            }
            break;
        }
      case UART_THRE_INT:
        uart_can_send = true;
        sys_outb(UART_COM1_BASE_ADDR + UART_RBR, 'x');
        break;
      default:
        break;
    }
  }
}

int(video_test_init)(uint16_t mode, uint8_t delay)
{
  uart_com1_hook_id = 4;
  int irq_set_uart_com1 = BIT(uart_com1_hook_id);
  sys_irqsetpolicy(4, IRQ_EXCLUSIVE | IRQ_REENABLE, &uart_com1_hook_id);
  sys_outb(UART_COM1_BASE_ADDR + UART_LCR, (BIT(1) | BIT(0) | BIT(3)));
  sys_outb(UART_COM1_BASE_ADDR + UART_IER, (BIT(0) | BIT(1)));
  sys_outb(UART_COM1_BASE_ADDR + UART_FCR, BIT(0));

  int ipc_status;
  message msg;
  while(1) {
    if ( (driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
        switch (_ENDPOINT_P(msg.m_source)) {
            case HARDWARE:
                if (msg.m_notify.interrupts & irq_set_uart_com1)
                    uart_ih();
            break;
            default:
            break;
        }
    }
  }
  sys_irqrmpolicy(&uart_com1_hook_id);
}
