// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>

#include <stdbool.h>
#include <stdint.h>

// Any header files included below this line should have been created by you
#include "rtc.h"
#include "player.h"
#include "graphics.h"
#include "i8042.h"
#include "kbd.h"
#include "utils.h"
#include "entities.h"
#include "enemies.h"
#include "sprites/sprites.h"
#include "grid.h"
#include "mouse.h"
#include "uart.h"
#include <stdlib.h>
#include "game_helper.h"

extern uint8_t kbd_data;
extern struct packet mouse_pack;
extern bool rtc_alarm_occurred;
extern uint8_t uart_com1_data;
extern bool uart_read_error;

int main(int argc, char *argv[])
{
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/proj/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/proj/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

static int print_usage()
{
  printf("USAGE\nlcom_run proj [absolute path to xpm files] \n\n\n[absolute path to xpm files] default value = 'home/lcom/labs/proj/sprites/xpm_files/'\n\n");
  return 1;
}

// param path to xpm
int(proj_main_loop)(int argc, char *argv[])
{
  //change
  if (argc >= 2)
    return print_usage();

  char path[100] = "home/lcom/labs/proj/sprites/xpm_files/";

  if (argc == 0)
  {
    realloc(argv, sizeof(char *) * (argc + 1));
    argv[argc] = path;
  }

  //GAME PREPARATIONS

  struct Game game;
  game.game_state.gamemode = SINGLEPLAYER;
  game.game_state.menu = MAIN_MENU;
  game.game_state.difficulty = EASY;
  game.player_1 = NULL;
  game.player_2 = NULL;
  game.cursor = create_cursor();
  game.game_frame = 0;
  game.sync_frame = 0;
  game.action_request_player_1 = SPEARMAN_NO_ACT;
  game.action_request_player_2 = SPEARMAN_NO_ACT;
  game.sync_state = FIRST_STEP;
  game.player_num = PLAYER_1;
  game.background_generated = false;
  game.gameEnded = false;

  memset(grid, 0, sizeof(grid[0][0]) * GridY * GridX);

  generate_board_tileset_sprites(argv[0]);

  generate_spearman_sprites(argv[0]);

  generate_green_blob_sprites(argv[0]);

  generate_UI_sprites(argv[0]);

  //sleep(10);
  //GAME START

  if (vg_init_ours())
    printf("vg_init_ours failed");

  uint8_t kbd_bit_no = 0;
  kbd_subscribe_int(&kbd_bit_no);
  int irq_set_kbd = BIT(kbd_bit_no);

  uint8_t timer_bit_no = 1;
  timer_subscribe_int(&timer_bit_no);
  int irq_set_timer = BIT(timer_bit_no);

  mouse_write_command(MOUSE_STREAM);
  mouse_write_command(MOUSE_EN_DATA_REP);
  uint8_t mouse_bit_no = 2;
  mouse_subscribe_int(&mouse_bit_no);
  int irq_set_mouse = BIT(mouse_bit_no);

  uint8_t rtc_bit_no = 3;
  rtc_subscribe_int(&rtc_bit_no);
  int irq_set_rtc = BIT(rtc_bit_no);

  int irq_set_uart_com1;
  uint8_t uart_com1_bit_no = 4;
  uart_com1_subscribe_int(&uart_com1_bit_no);
  irq_set_uart_com1 = BIT(uart_com1_bit_no);
  //SET UP THE UART FOR RX INTERRUPTS
  sys_outb(UART_COM1_BASE_ADDR + UART_LCR, (BIT(1) | BIT(0) | BIT(3)));
  sys_outb(UART_COM1_BASE_ADDR + UART_IER, BIT(0));
  sys_outb(UART_COM1_BASE_ADDR + UART_FCR, (BIT(0) | BIT(1) | BIT(2)));

  //SET UP THE RTC
  uint8_t regA;
  uint8_t regB;
  uint8_t regC;
  rtc_read_register(RTC_REG_A, &regA);
  rtc_read_register(RTC_REG_B, &regB);
  rtc_read_register(RTC_REG_C, &regC);
  rtc_write_register(RTC_REG_B, regB | RTC_UIE | RTC_AIE);

  int ipc_status;
  message msg;

  while (!uart_read_error && !game.gameEnded) //main game loop
  {
    if ((driver_receive(ANY, &msg, &ipc_status)) != 0)
    {
      continue;
    }
    if (is_ipc_notify(ipc_status))
    {
      switch (_ENDPOINT_P(msg.m_source))
      {
      case HARDWARE:
        if (msg.m_notify.interrupts & irq_set_kbd)
        {
          kbd_ih();
          if (kbd_parse_data() != NOT_READY)
          {
            process_kbd_input(&game);
          }
        }
        if (msg.m_notify.interrupts & irq_set_mouse)
        {
          mouse_ih();
          if (!mouse_parse_data())
          {
            process_mouse_input(&game);
          }
        }
        if (msg.m_notify.interrupts & irq_set_rtc)
        {
          rtc_ih();
        }
        if (msg.m_notify.interrupts & irq_set_uart_com1)
        {
          uart_ih();
          process_uart_packet(&game);
        }
        if (msg.m_notify.interrupts & irq_set_timer)
        {
          on_timer_int(&game);
        }
        break;
      default:
        break;
      }
    }
  }

  //reset RTC registers to initial state
  rtc_write_register(RTC_REG_A, regA);
  rtc_write_register(RTC_REG_B, regB);
  rtc_write_register(RTC_REG_C, regC);

  //unsubscribe interrupts
  rtc_unsubscribe_int();
  kbd_unsubscribe_int();
  mouse_unsubscribe_int();
  mouse_write_command(MOUSE_DIS_DATA_REP);
  timer_unsubscribe_int();
  sys_outb(UART_COM1_BASE_ADDR + UART_FCR, BIT(1) | BIT(2));
  uart_com1_unsubscribe_int();

  //close graphics mode
  vg_exit_ours();

  //free memory
  delete_grid();
  sprite_cleanup();
  return 0;
}
