#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>
#include "game_helper.h"

extern uint8_t kbd_data;
extern struct packet mouse_pack;
extern uint8_t uart_com1_data;
extern bool rtc_alarm_occurred;

void process_kbd_input(struct Game *game)
{
  if (game->game_state.menu == IN_GAME)
  {
    switch (kbd_data)
    {
    case S_MAKE:
      if (game->player_num == PLAYER_1)
      {
        game->action_request_player_1 = SPEARMAN_MOVE_DOWN;
        if (game->game_state.gamemode == COOP)
          send_data_uart((char)game->action_request_player_1);
      }
      else if (game->game_state.gamemode == COOP && game->player_num == PLAYER_2)
      {
        game->action_request_player_2 = SPEARMAN_MOVE_DOWN;
        if (game->game_state.gamemode == COOP)
          send_data_uart((char)game->action_request_player_2);
      }
      break;
    case D_MAKE:
      if (game->player_num == PLAYER_1)
      {
        game->action_request_player_1 = SPEARMAN_MOVE_RIGHT;
        if (game->game_state.gamemode == COOP)
          send_data_uart((char)game->action_request_player_1);
      }
      else if (game->game_state.gamemode == COOP && game->player_num == PLAYER_2)
      {
        game->action_request_player_2 = SPEARMAN_MOVE_RIGHT;
        if (game->game_state.gamemode == COOP)
          send_data_uart((char)game->action_request_player_2);
      }
      break;
    case W_MAKE:
      if (game->player_num == PLAYER_1)
      {
        game->action_request_player_1 = SPEARMAN_MOVE_UP;
        if (game->game_state.gamemode == COOP)
          send_data_uart((char)game->action_request_player_1);
      }
      else if (game->game_state.gamemode == COOP && game->player_num == PLAYER_2)
      {
        game->action_request_player_2 = SPEARMAN_MOVE_UP;
        if (game->game_state.gamemode == COOP)
          send_data_uart((char)game->action_request_player_2);
      }
      break;
    case A_MAKE:
      if (game->player_num == PLAYER_1)
      {
        game->action_request_player_1 = SPEARMAN_MOVE_LEFT;
        if (game->game_state.gamemode == COOP)
          send_data_uart((char)game->action_request_player_1);
      }
      else if (game->game_state.gamemode == COOP && game->player_num == PLAYER_2)
      {
        game->action_request_player_2 = SPEARMAN_MOVE_LEFT;
        if (game->game_state.gamemode == COOP)
          send_data_uart((char)game->action_request_player_2);
      }
      break;
    case SP_MAKE:
      if (game->player_num == PLAYER_1)
      {
        game->action_request_player_1 = SPEARMAN_ATTACK;
        if (game->game_state.gamemode == COOP)
          send_data_uart((char)game->action_request_player_1);
      }
      else if (game->game_state.gamemode == COOP && game->player_num == PLAYER_2)
      {
        game->action_request_player_2 = SPEARMAN_ATTACK;
        if (game->game_state.gamemode == COOP)
          send_data_uart((char)game->action_request_player_2);
      }
      break;
    case Q_MAKE:
      if ((game->player_num == PLAYER_1) && !(((struct SpearMan *)(game->player_1)->entity_info)->special_in_cd))
      {
        ((struct SpearMan *)(game->player_1)->entity_info)->channeling_special = true;
      }
      else if ((game->game_state.gamemode == COOP && game->player_num == PLAYER_2) && !(((struct SpearMan *)(game->player_2)->entity_info)->special_in_cd))
      {
        ((struct SpearMan *)(game->player_2)->entity_info)->channeling_special = true;
      }
      break;
    default:
      break;
    }
  }
  if (kbd_data == (ESC_MAKE | BREAKC))
  {
    switch (game->game_state.menu)
    {
    case VICTORY:
    case LOST:
    case IN_GAME:
      if(game->game_state.gamemode == COOP)
      {
        send_data_uart('L');
      }
      game->game_state.menu = MAIN_MENU;
      game->background_generated = false;
      game->player_num = PLAYER_1;
      delete_grid();
      break;
    case DIFFICULTY_MENU:
      game->game_state.menu = MAIN_MENU;
      break;
    case MAIN_MENU:
      game->game_state.menu = EXIT;
      break;
    default:
      break;
    }
  }
}

void create_enemies(struct Game game)
{
  uint8_t h, m, s;
  rtc_read_time(&h, &m, &s);
  srandom(h * 3600 + m * 60 + (game.game_state.gamemode == SINGLEPLAYER) * s);
  struct Entity *blobby;
  int no_green_blobs = 15 * (game.game_state.difficulty + 1);
  for (int i = 0; i < no_green_blobs; i++)
  {
    blobby = create_g_blob(random() % GridX, random() % GridY, random() % 4);
    if (grid_add(blobby))
      i--;
  }
}

void process_mouse_input(struct Game* game)
{
  update_mouse_position(game->cursor, mouse_pack.delta_x, mouse_pack.delta_y);
  if (game->game_state.menu == IN_GAME)
  {
    if (mouse_pack.lb && ((struct SpearMan *)(game->player_1)->entity_info)->channeling_special && game->player_num == PLAYER_1)
    {
      if (!((((struct SpearMan *)(game->player_1)->entity_info)->target_x == ((struct SpearMan *)(game->player_1)->entity_info)->x && ((struct SpearMan *)(game->player_1)->entity_info)->target_y == ((struct SpearMan *)(game->player_1)->entity_info)->y) || (!(((struct SpearMan *)(game->player_1)->entity_info)->target_x == ((struct SpearMan *)(game->player_1)->entity_info)->x && ((struct SpearMan *)(game->player_1)->entity_info)->target_y <= ((struct SpearMan *)(game->player_1)->entity_info)->y + ((struct SpearMan *)(game->player_1)->entity_info)->special_range && ((struct SpearMan *)(game->player_1)->entity_info)->target_y >= (char)(((struct SpearMan *)(game->player_1)->entity_info)->y - ((struct SpearMan *)(game->player_1)->entity_info)->special_range)) && !(((struct SpearMan *)(game->player_1)->entity_info)->target_y == ((struct SpearMan *)(game->player_1)->entity_info)->y && ((struct SpearMan *)(game->player_1)->entity_info)->target_x <= ((struct SpearMan *)(game->player_1)->entity_info)->x + ((struct SpearMan *)(game->player_1)->entity_info)->special_range && ((struct SpearMan *)(game->player_1)->entity_info)->target_x >= (char)(((struct SpearMan *)(game->player_1)->entity_info)->x - ((struct SpearMan *)(game->player_1)->entity_info)->special_range)))))
      {
        if (((struct SpearMan *)(game->player_1)->entity_info)->target_x > ((struct SpearMan *)(game->player_1)->entity_info)->x)
          game->action_request_player_1 = SPEARMAN_SPECIAL_RIGHT;
        else if (((struct SpearMan *)(game->player_1)->entity_info)->target_x < ((struct SpearMan *)(game->player_1)->entity_info)->x)
          game->action_request_player_1 = SPEARMAN_SPECIAL_LEFT;
        else if (((struct SpearMan *)(game->player_1)->entity_info)->target_y > ((struct SpearMan *)(game->player_1)->entity_info)->y)
          game->action_request_player_1 = SPEARMAN_SPECIAL_DOWN;
        else if (((struct SpearMan *)(game->player_1)->entity_info)->target_y < ((struct SpearMan *)(game->player_1)->entity_info)->y)
          game->action_request_player_1 = SPEARMAN_SPECIAL_UP;
        if (game->game_state.gamemode == COOP)
          send_data_uart((char)game->action_request_player_1);
      }
    }
    else if (mouse_pack.lb && ((struct SpearMan *)(game->player_2)->entity_info)->channeling_special && game->player_num == PLAYER_2)
    {
      if (!((((struct SpearMan *)(game->player_2)->entity_info)->target_x == ((struct SpearMan *)(game->player_2)->entity_info)->x && ((struct SpearMan *)(game->player_2)->entity_info)->target_y == ((struct SpearMan *)(game->player_2)->entity_info)->y) || (!(((struct SpearMan *)(game->player_2)->entity_info)->target_x == ((struct SpearMan *)(game->player_2)->entity_info)->x && ((struct SpearMan *)(game->player_2)->entity_info)->target_y <= ((struct SpearMan *)(game->player_2)->entity_info)->y + ((struct SpearMan *)(game->player_2)->entity_info)->special_range && ((struct SpearMan *)(game->player_2)->entity_info)->target_y >= (char)(((struct SpearMan *)(game->player_2)->entity_info)->y - ((struct SpearMan *)(game->player_2)->entity_info)->special_range)) && !(((struct SpearMan *)(game->player_2)->entity_info)->target_y == ((struct SpearMan *)(game->player_2)->entity_info)->y && ((struct SpearMan *)(game->player_2)->entity_info)->target_x <= ((struct SpearMan *)(game->player_2)->entity_info)->x + ((struct SpearMan *)(game->player_2)->entity_info)->special_range && ((struct SpearMan *)(game->player_2)->entity_info)->target_x >= (char)(((struct SpearMan *)(game->player_2)->entity_info)->x - ((struct SpearMan *)(game->player_2)->entity_info)->special_range)))))
      {
        if (((struct SpearMan *)(game->player_2)->entity_info)->target_x > ((struct SpearMan *)(game->player_2)->entity_info)->x)
          game->action_request_player_2 = SPEARMAN_SPECIAL_RIGHT;
        else if (((struct SpearMan *)(game->player_2)->entity_info)->target_x < ((struct SpearMan *)(game->player_2)->entity_info)->x)
          game->action_request_player_2 = SPEARMAN_SPECIAL_LEFT;
        else if (((struct SpearMan *)(game->player_2)->entity_info)->target_y > ((struct SpearMan *)(game->player_2)->entity_info)->y)
          game->action_request_player_2 = SPEARMAN_SPECIAL_DOWN;
        else if (((struct SpearMan *)(game->player_2)->entity_info)->target_y < ((struct SpearMan *)(game->player_2)->entity_info)->y)
          game->action_request_player_2 = SPEARMAN_SPECIAL_UP;
        if (game->game_state.gamemode == COOP)
          send_data_uart((char)game->action_request_player_2);
      }
    }
    if (mouse_pack.rb && ((struct SpearMan *)(game->player_1)->entity_info)->channeling_special && game->player_num == PLAYER_1)
      ((struct SpearMan *)(game->player_1)->entity_info)->channeling_special = false;
    else if (mouse_pack.rb && ((struct SpearMan *)(game->player_2)->entity_info)->channeling_special && game->player_num == PLAYER_2)
      ((struct SpearMan *)(game->player_2)->entity_info)->channeling_special = false;
  }
  else if (game->game_state.menu == MAIN_MENU && mouse_pack.lb)
  {
    if (game->cursor->x >= 202 - 15 && game->cursor->x <= 334 + 15 && game->cursor->y >= 400 - 10 && game->cursor->y <= 414 + 10)
    {
      game->game_state.menu = DIFFICULTY_MENU;
      game->game_state.gamemode = SINGLEPLAYER;
    }
    else if (game->cursor->x >= 532 - 15 && game->cursor->x <= 576 + 15 && game->cursor->y >= 400 - 10 && game->cursor->y <= 414 + 10)
    {
      game->game_state.menu = DIFFICULTY_MENU;
      game->game_state.gamemode = COOP;
    }
  }
  else if (game->game_state.menu == DIFFICULTY_MENU && mouse_pack.lb)
  {
    if (game->cursor->x >= 175 - 15 && game->cursor->x <= 175 + 11 * 4 + 15 && game->cursor->y >= 400 - 10 && game->cursor->y <= 414 + 10)
    {
      game->game_state.difficulty = EASY;
      if (game->game_state.gamemode)
        game->game_state.menu = SYNCING;
      else
        game->game_state.menu = IN_GAME;
    }
    else if (game->cursor->x >= 353 - 15 && game->cursor->x <= 353 + 11 * 6 + 15 && game->cursor->y >= 400 - 10 && game->cursor->y <= 414 + 10)
    {
      game->game_state.difficulty = MEDIUM;
      if (game->game_state.gamemode)
        game->game_state.menu = SYNCING;
      else
        game->game_state.menu = IN_GAME;
    }
    else if (game->cursor->x >= 575 - 15 && game->cursor->x <= 575 + 11 * 4 + 15 && game->cursor->y >= 400 - 10 && game->cursor->y <= 414 + 10)
    {
      game->game_state.difficulty = HARD;
      if (game->game_state.gamemode)
        game->game_state.menu = SYNCING;
      else
        game->game_state.menu = IN_GAME;
    }
    if (game->game_state.menu == IN_GAME)
    {
      game->player_1 = create_spearman(0, 0);
      grid_add(game->player_1);
      create_enemies(*game);
      create_background();
    }
  }
}

void process_uart_packet(struct Game* game)
{
  if (game->game_state.gamemode == COOP)
  {
    switch (game->game_state.menu)
    {
    case SYNCING:
      if (sync_players(&game->player_num, &game->sync_state, uart_com1_data))
      {
        game->game_state.menu = IN_GAME;
        game->player_2 = create_spearman(0, 1);
        grid_add(game->player_2);
        game->player_1 = create_spearman(0, 0);
        grid_add(game->player_1);
        create_enemies(*game);
        create_background();
        game->sync_state = FIRST_STEP;
      }
      break;
    case IN_GAME:
      if(uart_com1_data == 'L') //other player left to main menu
      {
        game->game_state.menu = MAIN_MENU;
        game->background_generated = false;
        delete_grid();
      }
      if (game->player_num == PLAYER_1)
        game->action_request_player_2 = (enum SpearmanAction)uart_com1_data;
      else
        game->action_request_player_1 = (enum SpearmanAction)uart_com1_data;
      break;
    default:
      break;
    }
  }
}

void on_timer_int(struct Game* game)
{
  switch (game->game_state.menu)
  {
  case SYNCING:
    if (game->sync_state == FIRST_STEP)
    {
      sync_first_step(&game->player_num, uart_com1_data);
      game->sync_state++;
    }
    if (game->sync_frame == 600)
    {
      game->game_state.menu = MAIN_MENU;
      game->sync_state = FIRST_STEP;
    }
    if (!game->background_generated)
    {
      game->background_generated = true;
      paint_xpm(menu_background, 0, 0, true);
    }
    background_refresh();
    paint_text("SYNCHRONIZING", 329, 400, false);
    paint_text("10 SECOND TIMEOUT", 307, 424, false);
    game->sync_frame++;
    break;
  case IN_GAME:
    if (rtc_alarm_occurred)
    {
      if (game->player_num == PLAYER_1)
      {
        ((struct SpearMan *)game->player_1->entity_info)->special_in_cd = false;
        rtc_alarm_occurred = false;
      }
      else
      {
        ((struct SpearMan *)game->player_2->entity_info)->special_in_cd = false;
        rtc_alarm_occurred = false;
      }
    }
    if (game->player_num == PLAYER_1 && ((struct SpearMan *)game->player_1->entity_info)->channeling_special)
      mouse_grid_pos(game->cursor, &((struct SpearMan *)game->player_1->entity_info)->target_x, &((struct SpearMan *)game->player_1->entity_info)->target_y);
    else if (game->player_num == PLAYER_2 && ((struct SpearMan *)game->player_2->entity_info)->channeling_special)
      mouse_grid_pos(game->cursor, &((struct SpearMan *)game->player_2->entity_info)->target_x, &((struct SpearMan *)game->player_2->entity_info)->target_y);
    //"on new cycle"
    if (game->game_frame % sys_hz() == 0)
    {
      spearman_act((struct SpearMan *)game->player_1->entity_info, game->action_request_player_1);
      game->action_request_player_1 = SPEARMAN_NO_ACT;
      if (game->game_state.gamemode == COOP)
      {
        spearman_act((struct SpearMan *)game->player_2->entity_info, game->action_request_player_2);
        game->action_request_player_2 = SPEARMAN_NO_ACT;
      }
    }
    if (game->game_frame % sys_hz() == 30)
    {
      if (grid_enemies_move())
      {
        game->game_state.menu = VICTORY;
        game->background_generated = false;
        game->sync_state = FIRST_STEP;
      }
    }
    background_refresh();
    if (game->player_num == PLAYER_1)
      paint_UI((struct SpearMan *)game->player_1->entity_info);
    else
      paint_UI((struct SpearMan *)game->player_2->entity_info);
    //entity update - animations and such
    if (update_animations(game->game_frame)) //if an enemy killed any player and the animation ended
    {
      game->game_state.menu = LOST;
      game->background_generated = false;
      game->sync_state = FIRST_STEP;
    }
    paint_grid();
    paint_background_lateral_walls();
    game->game_frame++;
    break;
  case MAIN_MENU:
    if (!game->background_generated)
    {
      game->sync_frame = 0;
      game->game_frame = 0;
      game->background_generated = true;
      paint_xpm(menu_background, 0, 0, true);
    }
    background_refresh();
    paint_text("SINGLEPLAYER", 202, 400, false);
    paint_text("COOP", 532, 400, false);
    paint_text("PRESS ESC TO EXIT THE GAME", 0, 586, false);
    break;
  case DIFFICULTY_MENU:
    if (!game->background_generated)
    {
      game->background_generated = true;
      paint_xpm(menu_background, 0, 0, true);
    }
    background_refresh();
    paint_text("EASY", 175, 400, false);
    paint_text("MEDIUM", 353, 400, false);
    paint_text("HARD", 575, 400, false);
    paint_text("PRESS ESC TO GO BACK", 0, 586, false);
    break;
  case VICTORY:
    if (!game->background_generated)
    {
      game->background_generated = true;
      paint_xpm(winning_background, 0, 0, true);
    }
    background_refresh();
    paint_text("YOU WIN!", 367, 300, false);
    paint_text("PRESS ESC TO GO TO THE MAIN MENU", 0, 586, false);
    break;
  case LOST:
    if (!game->background_generated)
    {
      game->background_generated = true;
      paint_area(0, 0, 800, 600, 0, true);
    }
    background_refresh();
    paint_text("HEH, YOU DIED? BETTER LUCK NEXT TIME...", 200, 300, false);
    paint_text("PRESS ESC TO GO TO THE MAIN MENU", 0, 586, false);
    break;
  case EXIT:
    game->gameEnded = true;
    break;
  }
  paint_cursor(game->cursor);
  video_refresh();
}
