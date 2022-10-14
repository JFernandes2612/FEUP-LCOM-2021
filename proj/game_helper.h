#ifndef GAME_HELPER_H
#define GAME_HELPER_H

#include "uart.h"
#include "player.h"
#include "grid.h"
#include "i8042.h"
#include "rtc.h"
#include "enemies.h"
#include "graphics.h"

/**
 * @brief Represents the gamemode the player is playing
 * @enum Gamemode
 */
enum Gamemode
{
    SINGLEPLAYER, /**< Single player mode */
    COOP          /**< Coop mode */
};

/**
 * @brief Represents the current game menu
 * @enum Menu
 */
enum Menu
{
    MAIN_MENU,       /**< Main menu */
    DIFFICULTY_MENU, /**< Difficulty menu */
    SYNCING,         /**< Syncing with the other player (COOP) */
    IN_GAME,         /**< In game (player) */
    VICTORY,         /**< Victory screen */
    LOST,            /**< Lost screen */
    EXIT             /**< EXIT game */
};

/**
 * @brief Represents the in game difficulty
 * @enum Difficulty
 */
enum Difficulty
{
    EASY,   /**< Easy difficulty */
    MEDIUM, /**< Medium difficulty */
    HARD    /**< Hard difficulty */
};

/**
 * @brief Struct that holds information on current gamemode, menu and difficulty
 * @struct GameState
 */
struct GameState
{
    enum Gamemode gamemode;     /**< Game mode */
    enum Menu menu;             /**< Current menu */
    enum Difficulty difficulty; /**< Game difficulty */
};

/**
 * @brief Struct that holds information on ALL the current game variables, excluding the grid
 * @struct Game
 */
struct Game
{
    struct GameState game_state;
    enum SyncState sync_state;
    struct Entity *player_1;
    struct Entity *player_2;
    struct Cursor* cursor;
    enum Player player_num;
    uint32_t game_frame;
    uint16_t sync_frame;
    enum SpearmanAction action_request_player_1;
    enum SpearmanAction action_request_player_2;
    bool background_generated;
    bool gameEnded;
};

/**
 * @brief Processes the input that comes from the keyboard and executes the associated logic
 *
 * @param game Current game state to be read and updated
 */
void process_kbd_input(struct Game *game);

/**
 * @brief Generates the random enemy board on the grid
 *
 * @param game Current game state to be read
 *
 * @note For convenience, this function already generates the random game seed based on current RTC reading
 */
void create_enemies(struct Game game);

/**
 * @brief Processes the input that comes from the mouse and executes the associated logic
 * 
 * @param game Current game state to be read and updated
 */
void process_mouse_input(struct Game* game);

/**
 * @brief Processes the incoming packet from the UART (COM1) and executes the associated logic
 * 
 * @param game Current game state to be read and updated
 */
void process_uart_packet(struct Game* game);

/**
 * @brief Performs all game logic and displaying that occurs every frame depending on the game state
 * 
 * @param game Current game state to be read and updated
 */
void on_timer_int(struct Game* game);
#endif
