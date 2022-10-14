#ifndef SPRITES_H
#define SPRITES_H

#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>

/**
 * @brief Number of spearman direction sprites
 */
#define NUM_OF_SPEARMAN_DIRECTIONS 4
/**
 * @brief Number of spearman attack sprites in each direction
 */
#define NUM_OF_SPEARMAN_ATTACK_SPRITES 8
/**
 * @brief Number of spearman death sprites in each direction
 */
#define NUM_OF_SPEARMAN_DEATH_SPRITES 8
/**
 * @brief Number of spearman move sprites in each direction
 */
#define NUM_OF_SPEARMAN_MOVE_SPRITES 10

/**
 * @brief Number of green blob directions
 */
#define NUM_OF_GREEN_BLOB_DIRECTIONS 4
/**
 * @brief Number of green blob idle sprites
 */
#define NUM_OF_GREEN_BLOB_IDLE_SPITES 4
/**
 * @brief Number of green blob move sprites in each direction
 */
#define NUM_OF_GREEN_BLOB_MOVE_SPRITES 8
/**
 * @brief Number of green blob death sprites
 */
#define NUM_OF_GREEN_BLOB_DEATH_SPRITES 9
/**
 * @brief Number of green blob attack sprites
 */
#define NUM_OF_GREEN_BLOB_ATTACK_SPRITES 5

/**
 * @brief Number of letters in the alphabet
 */
#define NUM_OF_LETTERS 26

/**
 * @struct GridImage
 * @brief Create a sprite whose drawing is done with offsets related to the grid postition
 */
struct GridImage
{
    /**
     * @brief Sprite
     */
    xpm_image_t *image;
    /**
     * @brief X offset
     */
    int x_offset;
    /**
     * @brief Y offset
     */
    int y_offset;
};

/**
 * @brief Create a grid image object
 *
 * @param image xpm sprite already decoded
 * @param x_offset x offset for the sprite related to the grid position
 * @param y_offset y offset for the sprite related to the grid position
 * @return struct GridImage*
 */
struct GridImage *(create_grid_image)(xpm_image_t *image, const int x_offset, const int y_offset);

/**
 * @brief Generates the floor tiles of the game board
 *
 * @param path string that has the main path to the folder to the xpm files
 */
void generate_board_tileset_sprites(char *path);

/**
 * @brief Generates the spearman sprites
 * @param path string that has the main path to the folder to the xpm files
 */
void generate_spearman_sprites(char *path);

/**
 * @brief generates the green blob sprites
 * @param path string that has the main path to the folder to the xpm files
 */
void generate_green_blob_sprites(char *path);

/**
 * @brief Generates the sprites for the game UI
 * @param path string that has the main path to the folder to the xpm files
 */
void generate_UI_sprites(char *path);

/**
 * @brief Cleans up the sprites (frees memory)
 */
void sprite_cleanup();

//GLOBAL SPRITES BACKGROUND
/**
 * @brief floor base tile
 */
xpm_image_t *floor_tile_1;
/**
 * @brief floor base tile 2 - with cracks
 */
xpm_image_t *floor_tile_2;
/**
 * @brief floor base tile 3 - with cracks
 */
xpm_image_t *floor_tile_3;
/**
 * @brief floor base tile with left shadow
 */
xpm_image_t *floor_tile_shadow;
/**
 * @brief top wall
 */
xpm_image_t *n_wall;
/**
 * @brief top wall with left shadow
 */
xpm_image_t *n_wall_shadow;
/**
 * @brief right wall - top view
 */
xpm_image_t *e_wall;
/**
 * @brief bottom wall - top view
 */
xpm_image_t *s_wall;
/**
 * @brief left wall - top view
 */
xpm_image_t *w_wall;
/**
 * @brief top wall - top view
 */
xpm_image_t *n_wall_top;
/**
 * @brief buttom left corner
 */
xpm_image_t *sw_corner;
/**
 * @brief buttom right corner
 */
xpm_image_t *se_corner;
/**
 * @brief top left corner
 */
xpm_image_t *nw_corner;
/**
 * @brief top right corner
 */
xpm_image_t *ne_corner;
/**
 * @brief Mouse cursor xpm
 */
xpm_image_t *mouse_cursor;

/**
 * @brief Border that represents the tiles that can be targeted for targeted abilities
 */
xpm_image_t *special_range_border;

/**
 * @brief Border that represents the tile that is beeing targeted for targeted a abilities
 */
xpm_image_t *special_range_selected_border;

/**
 * @brief Grid Images for the spearman direction sprites
 */
struct GridImage *spearman_direction_sprites[NUM_OF_SPEARMAN_DIRECTIONS];
/**
 * @brief Grid Images for the spearman attack sprites
 */
struct GridImage *spearman_attack_sprites[NUM_OF_SPEARMAN_DIRECTIONS][NUM_OF_SPEARMAN_ATTACK_SPRITES];
/**
 * @brief Grid Images for the spearman walk sprites
 */
struct GridImage *spearman_walk_sprites[NUM_OF_SPEARMAN_DIRECTIONS][NUM_OF_SPEARMAN_MOVE_SPRITES];
/**
 * @brief Grid Images for the spearman death sprites
 */
struct GridImage *spearman_death_sprites[NUM_OF_SPEARMAN_DIRECTIONS][NUM_OF_SPEARMAN_DEATH_SPRITES];

/**
 * @brief Spearman special ability sprite (left/right)
 */
xpm_image_t *spearman_special_e_w;

/**
 * @brief Spearman special ability sprite (upwards/downwards)
 */
xpm_image_t *spearman_special_n_s;

/**
 * @brief Grid Images for the green blob idle sprites
 */
struct GridImage *green_blob_idle_sprites[NUM_OF_GREEN_BLOB_IDLE_SPITES];
/**
 * @brief Grid Images for the green blob move sprites
 */
struct GridImage *green_blob_move_sprites[NUM_OF_GREEN_BLOB_DIRECTIONS][NUM_OF_GREEN_BLOB_MOVE_SPRITES];
/**
 * @brief Grid Images for the green blob death sprites
 */
struct GridImage *green_blob_death_sprites[NUM_OF_GREEN_BLOB_DEATH_SPRITES];
/**
 * @brief Grid Images for the green blob attack sprites
 */
struct GridImage *green_blob_attack_sprites[NUM_OF_GREEN_BLOB_DIRECTIONS][NUM_OF_GREEN_BLOB_ATTACK_SPRITES];

/**
 * @brief UI element that represents the health of a player (represents 1 life)
 */
xpm_image_t *UI_full_heart;

/**
 * @brief UI element that represents the health of a player (represents 0 lifes)
 */
xpm_image_t *UI_empty_heart;

/**
 * @brief UI element that indicates the speaman special ability
 */
xpm_image_t *spearman_special_UI;

/**
 * @brief Upper letters (text)
 */
xpm_image_t *upper_letters[NUM_OF_LETTERS];

/**
 * @brief Number 0
 */
xpm_image_t *zero;

/**
 * @brief Number 1
 */
xpm_image_t *one;

/**
 * @brief Final stop
 */
xpm_image_t *final_stop;

/**
 * @brief Comma
 */
xpm_image_t *comma;

/**
 * @brief Question Mark
 */
xpm_image_t *question_mark;

/**
 * @brief Exclamation Mark
 */
xpm_image_t *exclamation_mark;

/**
 * @brief Menu background
 */
xpm_image_t *menu_background;

/**
 * @brief winning screen background
 */
xpm_image_t *winning_background;

#endif
