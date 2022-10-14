#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>
#include "sprites.h"
#include "../graphics.h"
#include "xpm_files/background.h"
#include "xpm_files/winning_background.h"

static char cpy_buff[100];

struct GridImage *(create_grid_image)(xpm_image_t *image, const int x_offset, const int y_offset)
{
    struct GridImage *ret;
    ret = malloc(sizeof(*ret));
    ret->image = image;
    ret->x_offset = x_offset;
    ret->y_offset = y_offset;
    return ret;
}

void generate_board_tileset_sprites(char *path)
{
    floor_tile_1 = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    floor_tile_2 = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    floor_tile_3 = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    floor_tile_shadow = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    n_wall = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    n_wall_shadow = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    e_wall = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    w_wall = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    s_wall = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    n_wall_top = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    se_corner = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    sw_corner = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    ne_corner = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    nw_corner = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    //https://opengameart.org/content/dungeon-tileset-4
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "floor_tiles_1.xpm"), floor_tile_1);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "floor_tiles_2.xpm"), floor_tile_2);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "floor_tiles_3.xpm"), floor_tile_3);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "floor_tiles_shadow.xpm"), floor_tile_shadow);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "N_wall.xpm"), n_wall);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "N_wall_shadow.xpm"), n_wall_shadow);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "E_wall.xpm"), e_wall);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "W_wall.xpm"), w_wall);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "S_wall.xpm"), s_wall);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "N_wall_top.xpm"), n_wall_top);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "SW_corner.xpm"), sw_corner);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "SE_corner.xpm"), se_corner);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "NW_corner.xpm"), nw_corner);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "NE_corner.xpm"), ne_corner);
    //~https://opengameart.org/content/dungeon-tileset-4
}

void generate_spearman_sprites(char *path)
{
    //https://opengameart.org/content/spearman-bleeds-game-art by "Bleed" on http://remusprites.carbonmade.com/

    //IDLE
    xpm_image_t *spearman_s_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_n_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_e_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_w_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_S.xpm"), spearman_s_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_N.xpm"), spearman_n_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_E.xpm"), spearman_e_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_W.xpm"), spearman_w_xpm);
    struct GridImage *spearman_s = create_grid_image(spearman_s_xpm, -16, -35);
    struct GridImage *spearman_n = create_grid_image(spearman_n_xpm, -16, -35);
    struct GridImage *spearman_e = create_grid_image(spearman_e_xpm, -16, -38);
    struct GridImage *spearman_w = create_grid_image(spearman_w_xpm, -16, -38);
    struct GridImage *spearman_direction_sprites_copy[NUM_OF_SPEARMAN_DIRECTIONS] = {spearman_e, spearman_n, spearman_w, spearman_s};
    memcpy(&spearman_direction_sprites[0], &spearman_direction_sprites_copy[0], sizeof(struct GridImage *) * NUM_OF_SPEARMAN_DIRECTIONS);

    //WALK
    xpm_image_t *spearman_walk_e_1_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_walk_e_2_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_walk_e_3_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_walk_e_4_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_walk_e_5_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_walk_e_6_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_walk_e_7_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_walk_e_8_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_walk_e_9_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_walk_e_10_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_walk_e_1.xpm"), spearman_walk_e_1_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_walk_e_2.xpm"), spearman_walk_e_2_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_walk_e_3.xpm"), spearman_walk_e_3_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_walk_e_4.xpm"), spearman_walk_e_4_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_walk_e_5.xpm"), spearman_walk_e_5_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_walk_e_6.xpm"), spearman_walk_e_6_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_walk_e_7.xpm"), spearman_walk_e_7_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_walk_e_8.xpm"), spearman_walk_e_8_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_walk_e_9.xpm"), spearman_walk_e_9_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_walk_e_10.xpm"), spearman_walk_e_10_xpm);
    struct GridImage *spearman_walk_e_1 = create_grid_image(spearman_walk_e_1_xpm, -48, -38);
    struct GridImage *spearman_walk_e_2 = create_grid_image(spearman_walk_e_2_xpm, -46, -38);
    struct GridImage *spearman_walk_e_3 = create_grid_image(spearman_walk_e_3_xpm, -43, -38);
    struct GridImage *spearman_walk_e_4 = create_grid_image(spearman_walk_e_4_xpm, -39, -38);
    struct GridImage *spearman_walk_e_5 = create_grid_image(spearman_walk_e_5_xpm, -35, -38);
    struct GridImage *spearman_walk_e_6 = create_grid_image(spearman_walk_e_6_xpm, -31, -38);
    struct GridImage *spearman_walk_e_7 = create_grid_image(spearman_walk_e_7_xpm, -27, -38);
    struct GridImage *spearman_walk_e_8 = create_grid_image(spearman_walk_e_8_xpm, -23, -38);
    struct GridImage *spearman_walk_e_9 = create_grid_image(spearman_walk_e_9_xpm, -20, -38);
    struct GridImage *spearman_walk_e_10 = create_grid_image(spearman_walk_e_10_xpm, -18, -38);

    xpm_image_t *spearman_walk_n_1_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_walk_n_2_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_walk_n_3_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_walk_n_4_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_walk_n_5_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_walk_n_6_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_walk_n_7_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_walk_n_8_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_walk_n_9_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_walk_n_10_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_walk_n_1.xpm"), spearman_walk_n_1_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_walk_n_2.xpm"), spearman_walk_n_2_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_walk_n_3.xpm"), spearman_walk_n_3_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_walk_n_4.xpm"), spearman_walk_n_4_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_walk_n_5.xpm"), spearman_walk_n_5_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_walk_n_6.xpm"), spearman_walk_n_6_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_walk_n_7.xpm"), spearman_walk_n_7_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_walk_n_8.xpm"), spearman_walk_n_8_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_walk_n_9.xpm"), spearman_walk_n_9_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_walk_n_10.xpm"), spearman_walk_n_10_xpm);
    struct GridImage *spearman_walk_n_1 = create_grid_image(spearman_walk_n_1_xpm, -16, -3);
    struct GridImage *spearman_walk_n_2 = create_grid_image(spearman_walk_n_2_xpm, -16, -5);
    struct GridImage *spearman_walk_n_3 = create_grid_image(spearman_walk_n_3_xpm, -16, -8);
    struct GridImage *spearman_walk_n_4 = create_grid_image(spearman_walk_n_4_xpm, -16, -12);
    struct GridImage *spearman_walk_n_5 = create_grid_image(spearman_walk_n_5_xpm, -16, -16);
    struct GridImage *spearman_walk_n_6 = create_grid_image(spearman_walk_n_6_xpm, -16, -20);
    struct GridImage *spearman_walk_n_7 = create_grid_image(spearman_walk_n_7_xpm, -16, -29);
    struct GridImage *spearman_walk_n_8 = create_grid_image(spearman_walk_n_8_xpm, -16, -34);
    struct GridImage *spearman_walk_n_9 = create_grid_image(spearman_walk_n_9_xpm, -16, -34);
    struct GridImage *spearman_walk_n_10 = create_grid_image(spearman_walk_n_10_xpm, -16, -33);

    xpm_image_t *spearman_walk_w_1_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_walk_w_2_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_walk_w_3_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_walk_w_4_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_walk_w_5_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_walk_w_6_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_walk_w_7_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_walk_w_8_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_walk_w_9_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_walk_w_10_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_walk_w_1.xpm"), spearman_walk_w_1_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_walk_w_2.xpm"), spearman_walk_w_2_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_walk_w_3.xpm"), spearman_walk_w_3_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_walk_w_4.xpm"), spearman_walk_w_4_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_walk_w_5.xpm"), spearman_walk_w_5_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_walk_w_6.xpm"), spearman_walk_w_6_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_walk_w_7.xpm"), spearman_walk_w_7_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_walk_w_8.xpm"), spearman_walk_w_8_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_walk_w_9.xpm"), spearman_walk_w_9_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_walk_w_10.xpm"), spearman_walk_w_10_xpm);
    struct GridImage *spearman_walk_w_1 = create_grid_image(spearman_walk_w_1_xpm, 16, -38);
    struct GridImage *spearman_walk_w_2 = create_grid_image(spearman_walk_w_2_xpm, 14, -38);
    struct GridImage *spearman_walk_w_3 = create_grid_image(spearman_walk_w_3_xpm, 11, -38);
    struct GridImage *spearman_walk_w_4 = create_grid_image(spearman_walk_w_4_xpm, 7, -38);
    struct GridImage *spearman_walk_w_5 = create_grid_image(spearman_walk_w_5_xpm, 3, -38);
    struct GridImage *spearman_walk_w_6 = create_grid_image(spearman_walk_w_6_xpm, -1, -38);
    struct GridImage *spearman_walk_w_7 = create_grid_image(spearman_walk_w_7_xpm, -5, -38);
    struct GridImage *spearman_walk_w_8 = create_grid_image(spearman_walk_w_8_xpm, -9, -38);
    struct GridImage *spearman_walk_w_9 = create_grid_image(spearman_walk_w_9_xpm, -12, -38);
    struct GridImage *spearman_walk_w_10 = create_grid_image(spearman_walk_w_10_xpm, -14, -38);

    xpm_image_t *spearman_walk_s_1_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_walk_s_2_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_walk_s_3_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_walk_s_4_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_walk_s_5_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_walk_s_6_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_walk_s_7_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_walk_s_8_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_walk_s_9_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_walk_s_10_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_walk_s_1.xpm"), spearman_walk_s_1_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_walk_s_2.xpm"), spearman_walk_s_2_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_walk_s_3.xpm"), spearman_walk_s_3_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_walk_s_4.xpm"), spearman_walk_s_4_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_walk_s_5.xpm"), spearman_walk_s_5_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_walk_s_6.xpm"), spearman_walk_s_6_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_walk_s_7.xpm"), spearman_walk_s_7_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_walk_s_8.xpm"), spearman_walk_s_8_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_walk_s_9.xpm"), spearman_walk_s_9_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_walk_s_10.xpm"), spearman_walk_s_10_xpm);
    struct GridImage *spearman_walk_s_1 = create_grid_image(spearman_walk_s_1_xpm, -16, -67);
    struct GridImage *spearman_walk_s_2 = create_grid_image(spearman_walk_s_2_xpm, -16, -65);
    struct GridImage *spearman_walk_s_3 = create_grid_image(spearman_walk_s_3_xpm, -16, -62);
    struct GridImage *spearman_walk_s_4 = create_grid_image(spearman_walk_s_4_xpm, -16, -58);
    struct GridImage *spearman_walk_s_5 = create_grid_image(spearman_walk_s_5_xpm, -16, -54);
    struct GridImage *spearman_walk_s_6 = create_grid_image(spearman_walk_s_6_xpm, -16, -50);
    struct GridImage *spearman_walk_s_7 = create_grid_image(spearman_walk_s_7_xpm, -16, -46);
    struct GridImage *spearman_walk_s_8 = create_grid_image(spearman_walk_s_8_xpm, -16, -42);
    struct GridImage *spearman_walk_s_9 = create_grid_image(spearman_walk_s_9_xpm, -16, -39);
    struct GridImage *spearman_walk_s_10 = create_grid_image(spearman_walk_s_10_xpm, -16, -37);
    struct GridImage *spearman_walk_sprites_copy[NUM_OF_SPEARMAN_DIRECTIONS][NUM_OF_SPEARMAN_MOVE_SPRITES] = {{spearman_walk_e_1, spearman_walk_e_2, spearman_walk_e_3, spearman_walk_e_4, spearman_walk_e_5, spearman_walk_e_6, spearman_walk_e_7, spearman_walk_e_8, spearman_walk_e_9, spearman_walk_e_10},
                                                                                                              {spearman_walk_n_1, spearman_walk_n_2, spearman_walk_n_3, spearman_walk_n_4, spearman_walk_n_5, spearman_walk_n_6, spearman_walk_n_7, spearman_walk_n_8, spearman_walk_n_9, spearman_walk_n_10},
                                                                                                              {spearman_walk_w_1, spearman_walk_w_2, spearman_walk_w_3, spearman_walk_w_4, spearman_walk_w_5, spearman_walk_w_6, spearman_walk_w_7, spearman_walk_w_8, spearman_walk_w_9, spearman_walk_w_10},
                                                                                                              {spearman_walk_s_1, spearman_walk_s_2, spearman_walk_s_3, spearman_walk_s_4, spearman_walk_s_5, spearman_walk_s_6, spearman_walk_s_7, spearman_walk_s_8, spearman_walk_s_9, spearman_walk_s_10}};
    memcpy(&spearman_walk_sprites[0][0], &spearman_walk_sprites_copy[0][0], sizeof(struct GridImage *) * NUM_OF_SPEARMAN_DIRECTIONS * NUM_OF_SPEARMAN_MOVE_SPRITES);

    //ATTACK
    xpm_image_t *spearman_attack_e_1_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_attack_e_2_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_attack_e_3_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_attack_e_4_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_attack_e_5_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_attack_e_6_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_attack_e_7_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_attack_e_8_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_attack_e_1.xpm"), spearman_attack_e_1_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_attack_e_2.xpm"), spearman_attack_e_2_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_attack_e_3.xpm"), spearman_attack_e_3_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_attack_e_4.xpm"), spearman_attack_e_4_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_attack_e_5.xpm"), spearman_attack_e_5_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_attack_e_6.xpm"), spearman_attack_e_6_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_attack_e_7.xpm"), spearman_attack_e_7_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_attack_e_8.xpm"), spearman_attack_e_8_xpm);
    struct GridImage *spearman_attack_e_1 = create_grid_image(spearman_attack_e_1_xpm, -16, -38);
    struct GridImage *spearman_attack_e_2 = create_grid_image(spearman_attack_e_2_xpm, -27, -38);
    struct GridImage *spearman_attack_e_3 = create_grid_image(spearman_attack_e_3_xpm, -31, -38);
    struct GridImage *spearman_attack_e_4 = create_grid_image(spearman_attack_e_4_xpm, -27, -38);
    struct GridImage *spearman_attack_e_5 = create_grid_image(spearman_attack_e_5_xpm, -10, -38);
    struct GridImage *spearman_attack_e_6 = create_grid_image(spearman_attack_e_6_xpm, 0, -38);
    struct GridImage *spearman_attack_e_7 = create_grid_image(spearman_attack_e_7_xpm, -5, -38);
    struct GridImage *spearman_attack_e_8 = create_grid_image(spearman_attack_e_8_xpm, -12, -38);

    xpm_image_t *spearman_attack_n_1_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_attack_n_2_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_attack_n_3_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_attack_n_4_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_attack_n_5_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_attack_n_6_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_attack_n_7_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_attack_n_8_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_attack_n_1.xpm"), spearman_attack_n_1_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_attack_n_2.xpm"), spearman_attack_n_2_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_attack_n_3.xpm"), spearman_attack_n_3_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_attack_n_4.xpm"), spearman_attack_n_4_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_attack_n_5.xpm"), spearman_attack_n_5_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_attack_n_6.xpm"), spearman_attack_n_6_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_attack_n_7.xpm"), spearman_attack_n_7_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_attack_n_8.xpm"), spearman_attack_n_8_xpm);
    struct GridImage *spearman_attack_n_1 = create_grid_image(spearman_attack_n_1_xpm, -16, -35);
    struct GridImage *spearman_attack_n_2 = create_grid_image(spearman_attack_n_2_xpm, -14, -38);
    struct GridImage *spearman_attack_n_3 = create_grid_image(spearman_attack_n_3_xpm, -10, -38);
    struct GridImage *spearman_attack_n_4 = create_grid_image(spearman_attack_n_4_xpm, -10, -38);
    struct GridImage *spearman_attack_n_5 = create_grid_image(spearman_attack_n_5_xpm, -7, -38);
    struct GridImage *spearman_attack_n_6 = create_grid_image(spearman_attack_n_6_xpm, -10, -40); // 64 66
    struct GridImage *spearman_attack_n_7 = create_grid_image(spearman_attack_n_7_xpm, -10, -36);
    struct GridImage *spearman_attack_n_8 = create_grid_image(spearman_attack_n_8_xpm, -13, -36);

    xpm_image_t *spearman_attack_w_1_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_attack_w_2_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_attack_w_3_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_attack_w_4_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_attack_w_5_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_attack_w_6_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_attack_w_7_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_attack_w_8_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_attack_w_1.xpm"), spearman_attack_w_1_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_attack_w_2.xpm"), spearman_attack_w_2_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_attack_w_3.xpm"), spearman_attack_w_3_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_attack_w_4.xpm"), spearman_attack_w_4_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_attack_w_5.xpm"), spearman_attack_w_5_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_attack_w_6.xpm"), spearman_attack_w_6_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_attack_w_7.xpm"), spearman_attack_w_7_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_attack_w_8.xpm"), spearman_attack_w_8_xpm);
    struct GridImage *spearman_attack_w_1 = create_grid_image(spearman_attack_w_1_xpm, -16, -38);
    struct GridImage *spearman_attack_w_2 = create_grid_image(spearman_attack_w_2_xpm, -5, -38);
    struct GridImage *spearman_attack_w_3 = create_grid_image(spearman_attack_w_3_xpm, 0, -38);   // 68 64
    struct GridImage *spearman_attack_w_4 = create_grid_image(spearman_attack_w_4_xpm, -5, -38);  // 68 64
    struct GridImage *spearman_attack_w_5 = create_grid_image(spearman_attack_w_5_xpm, -22, -44); // 64 70
    struct GridImage *spearman_attack_w_6 = create_grid_image(spearman_attack_w_6_xpm, -32, -40); //64 66
    struct GridImage *spearman_attack_w_7 = create_grid_image(spearman_attack_w_7_xpm, -30, -38);
    struct GridImage *spearman_attack_w_8 = create_grid_image(spearman_attack_w_8_xpm, -20, -38);

    xpm_image_t *spearman_attack_s_1_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_attack_s_2_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_attack_s_3_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_attack_s_4_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_attack_s_5_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_attack_s_6_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_attack_s_7_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_attack_s_8_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_attack_s_1.xpm"), spearman_attack_s_1_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_attack_s_2.xpm"), spearman_attack_s_2_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_attack_s_3.xpm"), spearman_attack_s_3_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_attack_s_4.xpm"), spearman_attack_s_4_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_attack_s_5.xpm"), spearman_attack_s_5_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_attack_s_6.xpm"), spearman_attack_s_6_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_attack_s_7.xpm"), spearman_attack_s_7_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_attack_s_8.xpm"), spearman_attack_s_8_xpm);
    struct GridImage *spearman_attack_s_1 = create_grid_image(spearman_attack_s_1_xpm, -16, -35);
    struct GridImage *spearman_attack_s_2 = create_grid_image(spearman_attack_s_2_xpm, -16, -36);
    struct GridImage *spearman_attack_s_3 = create_grid_image(spearman_attack_s_3_xpm, -19, -40); // 64 70
    struct GridImage *spearman_attack_s_4 = create_grid_image(spearman_attack_s_4_xpm, -28, -44); // 64 75
    struct GridImage *spearman_attack_s_5 = create_grid_image(spearman_attack_s_5_xpm, -24, -38); // 64 66
    struct GridImage *spearman_attack_s_6 = create_grid_image(spearman_attack_s_6_xpm, -22, -36);
    struct GridImage *spearman_attack_s_7 = create_grid_image(spearman_attack_s_7_xpm, -22, -36);
    struct GridImage *spearman_attack_s_8 = create_grid_image(spearman_attack_s_8_xpm, -17, -36);
    struct GridImage *spearman_attack_sprites_copy[NUM_OF_SPEARMAN_DIRECTIONS][NUM_OF_SPEARMAN_ATTACK_SPRITES] = {{spearman_attack_e_1, spearman_attack_e_2, spearman_attack_e_3, spearman_attack_e_4, spearman_attack_e_5, spearman_attack_e_6, spearman_attack_e_7, spearman_attack_e_8},
                                                                                                                  {spearman_attack_n_1, spearman_attack_n_2, spearman_attack_n_3, spearman_attack_n_4, spearman_attack_n_5, spearman_attack_n_6, spearman_attack_n_7, spearman_attack_n_8},
                                                                                                                  {spearman_attack_w_1, spearman_attack_w_2, spearman_attack_w_3, spearman_attack_w_4, spearman_attack_w_5, spearman_attack_w_6, spearman_attack_w_7, spearman_attack_w_8},
                                                                                                                  {spearman_attack_s_1, spearman_attack_s_2, spearman_attack_s_3, spearman_attack_s_4, spearman_attack_s_5, spearman_attack_s_6, spearman_attack_s_7, spearman_attack_s_8}};
    memcpy(&spearman_attack_sprites[0][0], &spearman_attack_sprites_copy[0][0], sizeof(struct GridImage *) * NUM_OF_SPEARMAN_DIRECTIONS * NUM_OF_SPEARMAN_ATTACK_SPRITES);

    //DEATH
    xpm_image_t *spearman_death_e_1_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_death_e_2_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_death_e_3_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_death_e_4_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_death_e_5_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_death_e_6_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_death_e_7_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_death_e_8_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_death_e_1.xpm"), spearman_death_e_1_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_death_e_2.xpm"), spearman_death_e_2_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_death_e_3.xpm"), spearman_death_e_3_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_death_e_4.xpm"), spearman_death_e_4_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_death_e_5.xpm"), spearman_death_e_5_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_death_e_6.xpm"), spearman_death_e_6_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_death_e_7.xpm"), spearman_death_e_7_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_death_e_8.xpm"), spearman_death_e_8_xpm);
    struct GridImage *spearman_death_e_1 = create_grid_image(spearman_death_e_1_xpm, -16, -38);
    struct GridImage *spearman_death_e_2 = create_grid_image(spearman_death_e_2_xpm, -16, -38 + 3);
    struct GridImage *spearman_death_e_3 = create_grid_image(spearman_death_e_3_xpm, -16, -38 + 5);
    struct GridImage *spearman_death_e_4 = create_grid_image(spearman_death_e_4_xpm, -16, -38 + 7);
    struct GridImage *spearman_death_e_5 = create_grid_image(spearman_death_e_5_xpm, -16, -38 + 9);
    struct GridImage *spearman_death_e_6 = create_grid_image(spearman_death_e_6_xpm, -16, -38 + 11);
    struct GridImage *spearman_death_e_7 = create_grid_image(spearman_death_e_7_xpm, -16, -38 + 13);
    struct GridImage *spearman_death_e_8 = create_grid_image(spearman_death_e_8_xpm, -16, -38 + 15);

    xpm_image_t *spearman_death_n_1_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_death_n_2_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_death_n_3_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_death_n_4_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_death_n_5_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_death_n_6_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_death_n_7_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_death_n_8_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_death_n_1.xpm"), spearman_death_n_1_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_death_n_2.xpm"), spearman_death_n_2_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_death_n_3.xpm"), spearman_death_n_3_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_death_n_4.xpm"), spearman_death_n_4_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_death_n_5.xpm"), spearman_death_n_5_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_death_n_6.xpm"), spearman_death_n_6_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_death_n_7.xpm"), spearman_death_n_7_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_death_n_8.xpm"), spearman_death_n_8_xpm);
    struct GridImage *spearman_death_n_1 = create_grid_image(spearman_death_n_1_xpm, -16, -35);
    struct GridImage *spearman_death_n_2 = create_grid_image(spearman_death_n_2_xpm, -16, -35 + 3);
    struct GridImage *spearman_death_n_3 = create_grid_image(spearman_death_n_3_xpm, -16, -35 + 5);
    struct GridImage *spearman_death_n_4 = create_grid_image(spearman_death_n_4_xpm, -16, -35 + 7);
    struct GridImage *spearman_death_n_5 = create_grid_image(spearman_death_n_5_xpm, -16, -35 + 9);
    struct GridImage *spearman_death_n_6 = create_grid_image(spearman_death_n_6_xpm, -16, -35 + 11);
    struct GridImage *spearman_death_n_7 = create_grid_image(spearman_death_n_7_xpm, -16, -35 + 13);
    struct GridImage *spearman_death_n_8 = create_grid_image(spearman_death_n_8_xpm, -16, -35 + 15);

    xpm_image_t *spearman_death_w_1_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_death_w_2_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_death_w_3_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_death_w_4_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_death_w_5_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_death_w_6_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_death_w_7_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_death_w_8_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_death_w_1.xpm"), spearman_death_w_1_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_death_w_2.xpm"), spearman_death_w_2_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_death_w_3.xpm"), spearman_death_w_3_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_death_w_4.xpm"), spearman_death_w_4_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_death_w_5.xpm"), spearman_death_w_5_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_death_w_6.xpm"), spearman_death_w_6_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_death_w_7.xpm"), spearman_death_w_7_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_death_w_8.xpm"), spearman_death_w_8_xpm);
    struct GridImage *spearman_death_w_1 = create_grid_image(spearman_death_w_1_xpm, -16, -38);
    struct GridImage *spearman_death_w_2 = create_grid_image(spearman_death_w_2_xpm, -16, -38 + 3);
    struct GridImage *spearman_death_w_3 = create_grid_image(spearman_death_w_3_xpm, -16, -38 + 5);
    struct GridImage *spearman_death_w_4 = create_grid_image(spearman_death_w_4_xpm, -16, -38 + 7);
    struct GridImage *spearman_death_w_5 = create_grid_image(spearman_death_w_5_xpm, -16, -38 + 9);
    struct GridImage *spearman_death_w_6 = create_grid_image(spearman_death_w_6_xpm, -16, -38 + 11);
    struct GridImage *spearman_death_w_7 = create_grid_image(spearman_death_w_7_xpm, -16, -38 + 13);
    struct GridImage *spearman_death_w_8 = create_grid_image(spearman_death_w_8_xpm, -16, -38 + 15);

    xpm_image_t *spearman_death_s_1_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_death_s_2_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_death_s_3_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_death_s_4_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_death_s_5_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_death_s_6_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_death_s_7_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *spearman_death_s_8_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_death_s_1.xpm"), spearman_death_s_1_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_death_s_2.xpm"), spearman_death_s_2_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_death_s_3.xpm"), spearman_death_s_3_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_death_s_4.xpm"), spearman_death_s_4_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_death_s_5.xpm"), spearman_death_s_5_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_death_s_6.xpm"), spearman_death_s_6_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_death_s_7.xpm"), spearman_death_s_7_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_death_s_8.xpm"), spearman_death_s_8_xpm);
    struct GridImage *spearman_death_s_1 = create_grid_image(spearman_death_s_1_xpm, -16, -35);
    struct GridImage *spearman_death_s_2 = create_grid_image(spearman_death_s_2_xpm, -16, -35 + 3);
    struct GridImage *spearman_death_s_3 = create_grid_image(spearman_death_s_3_xpm, -16, -35 + 5);
    struct GridImage *spearman_death_s_4 = create_grid_image(spearman_death_s_4_xpm, -16, -35 + 7);
    struct GridImage *spearman_death_s_5 = create_grid_image(spearman_death_s_5_xpm, -16, -35 + 9);
    struct GridImage *spearman_death_s_6 = create_grid_image(spearman_death_s_6_xpm, -16, -35 + 11);
    struct GridImage *spearman_death_s_7 = create_grid_image(spearman_death_s_7_xpm, -16, -35 + 13);
    struct GridImage *spearman_death_s_8 = create_grid_image(spearman_death_s_8_xpm, -16, -35 + 15);
    struct GridImage *spearman_death_sprites_copy[NUM_OF_SPEARMAN_DIRECTIONS][NUM_OF_SPEARMAN_DEATH_SPRITES] = {{spearman_death_e_1, spearman_death_e_2, spearman_death_e_3, spearman_death_e_4, spearman_death_e_5, spearman_death_e_6, spearman_death_e_7, spearman_death_e_8},
                                                                                                                {spearman_death_n_1, spearman_death_n_2, spearman_death_n_3, spearman_death_n_4, spearman_death_n_5, spearman_death_n_6, spearman_death_n_7, spearman_death_n_8},
                                                                                                                {spearman_death_w_1, spearman_death_w_2, spearman_death_w_3, spearman_death_w_4, spearman_death_w_5, spearman_death_w_6, spearman_death_w_7, spearman_death_w_8},
                                                                                                                {spearman_death_s_1, spearman_death_s_2, spearman_death_s_3, spearman_death_s_4, spearman_death_s_5, spearman_death_s_6, spearman_death_s_7, spearman_death_s_8}};
    memcpy(&spearman_death_sprites[0][0], &spearman_death_sprites_copy[0][0], sizeof(struct GridImage *) * NUM_OF_SPEARMAN_DIRECTIONS * NUM_OF_SPEARMAN_DEATH_SPRITES);
    //~https://opengameart.org/content/spearman-bleeds-game-art by "Bleed" on http://remusprites.carbonmade.com/
}

void generate_green_blob_sprites(char *path)
{
    //https://opengameart.org/content/blob-sprite
    xpm_image_t *green_blob_idle_1_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *green_blob_idle_2_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *green_blob_idle_3_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *green_blob_idle_4_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "green_blob_idle_1.xpm"), green_blob_idle_1_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "green_blob_idle_2.xpm"), green_blob_idle_2_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "green_blob_idle_3.xpm"), green_blob_idle_3_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "green_blob_idle_4.xpm"), green_blob_idle_4_xpm);
    struct GridImage *green_blob_idle_1 = create_grid_image(green_blob_idle_1_xpm, 0, 2);
    struct GridImage *green_blob_idle_2 = create_grid_image(green_blob_idle_2_xpm, 0, 2);
    struct GridImage *green_blob_idle_3 = create_grid_image(green_blob_idle_3_xpm, 0, 2);
    struct GridImage *green_blob_idle_4 = create_grid_image(green_blob_idle_4_xpm, 0, 2);
    struct GridImage *green_blob_idle_sprites_copy[NUM_OF_GREEN_BLOB_IDLE_SPITES] = {green_blob_idle_1, green_blob_idle_2, green_blob_idle_3, green_blob_idle_4};
    memcpy(&green_blob_idle_sprites[0], &green_blob_idle_sprites_copy[0], sizeof(struct GridImage *) * NUM_OF_GREEN_BLOB_IDLE_SPITES);

    xpm_image_t *green_blob_move_1_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *green_blob_move_2_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *green_blob_move_3_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *green_blob_move_4_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *green_blob_move_5_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *green_blob_move_6_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *green_blob_move_7_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *green_blob_move_8_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "green_blob_move_1.xpm"), green_blob_move_1_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "green_blob_move_2.xpm"), green_blob_move_2_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "green_blob_move_3.xpm"), green_blob_move_3_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "green_blob_move_4.xpm"), green_blob_move_4_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "green_blob_move_5.xpm"), green_blob_move_5_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "green_blob_move_6.xpm"), green_blob_move_6_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "green_blob_move_7.xpm"), green_blob_move_7_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "green_blob_move_8.xpm"), green_blob_move_8_xpm);
    struct GridImage *green_blob_move_e_1 = create_grid_image(green_blob_move_1_xpm, -32, 2 - 3);
    struct GridImage *green_blob_move_e_2 = create_grid_image(green_blob_move_2_xpm, -32 + 5, 2 - 10);
    struct GridImage *green_blob_move_e_3 = create_grid_image(green_blob_move_3_xpm, -32 + 10, 2 - 15);
    struct GridImage *green_blob_move_e_4 = create_grid_image(green_blob_move_4_xpm, -32 + 15, 2 - 19);
    struct GridImage *green_blob_move_e_5 = create_grid_image(green_blob_move_5_xpm, -32 + 20, 2 - 30);
    struct GridImage *green_blob_move_e_6 = create_grid_image(green_blob_move_6_xpm, -32 + 25, 2 - 19);
    struct GridImage *green_blob_move_e_7 = create_grid_image(green_blob_move_7_xpm, -32 + 30, 2 - 15);
    struct GridImage *green_blob_move_e_8 = create_grid_image(green_blob_move_8_xpm, -32 + 35, 2 - 10);

    struct GridImage *green_blob_move_n_1 = create_grid_image(green_blob_move_1_xpm, 0, 2 + 32 - 3);
    struct GridImage *green_blob_move_n_2 = create_grid_image(green_blob_move_2_xpm, 0, 2 + 32 - 17);
    struct GridImage *green_blob_move_n_3 = create_grid_image(green_blob_move_3_xpm, 0, 2 + 32 - 30);
    struct GridImage *green_blob_move_n_4 = create_grid_image(green_blob_move_4_xpm, 0, 2 + 32 - 42);
    struct GridImage *green_blob_move_n_5 = create_grid_image(green_blob_move_5_xpm, 0, 2 + 32 - 50);
    struct GridImage *green_blob_move_n_6 = create_grid_image(green_blob_move_6_xpm, 0, 2 + 32 - 45);
    struct GridImage *green_blob_move_n_7 = create_grid_image(green_blob_move_7_xpm, 0, 2 + 32 - 38);
    struct GridImage *green_blob_move_n_8 = create_grid_image(green_blob_move_8_xpm, 0, 2 + 32 - 35);

    struct GridImage *green_blob_move_w_1 = create_grid_image(green_blob_move_1_xpm, 32, 2 - 3);
    struct GridImage *green_blob_move_w_2 = create_grid_image(green_blob_move_2_xpm, 32 - 5, 2 - 10);
    struct GridImage *green_blob_move_w_3 = create_grid_image(green_blob_move_3_xpm, 32 - 10, 2 - 15);
    struct GridImage *green_blob_move_w_4 = create_grid_image(green_blob_move_4_xpm, 32 - 15, 2 - 19);
    struct GridImage *green_blob_move_w_5 = create_grid_image(green_blob_move_5_xpm, 32 - 20, 2 - 30);
    struct GridImage *green_blob_move_w_6 = create_grid_image(green_blob_move_6_xpm, 32 - 25, 2 - 19);
    struct GridImage *green_blob_move_w_7 = create_grid_image(green_blob_move_7_xpm, 32 - 30, 2 - 15);
    struct GridImage *green_blob_move_w_8 = create_grid_image(green_blob_move_8_xpm, 32 - 35, 2 - 10);

    struct GridImage *green_blob_move_s_1 = create_grid_image(green_blob_move_1_xpm, 0, 2 - 32 + 3);
    struct GridImage *green_blob_move_s_2 = create_grid_image(green_blob_move_2_xpm, 0, 2 - 32 + 8);
    struct GridImage *green_blob_move_s_3 = create_grid_image(green_blob_move_3_xpm, 0, 2 - 32 + 12);
    struct GridImage *green_blob_move_s_4 = create_grid_image(green_blob_move_4_xpm, 0, 2 - 32 + 15);
    struct GridImage *green_blob_move_s_5 = create_grid_image(green_blob_move_5_xpm, 0, 2 - 32 + 17);
    struct GridImage *green_blob_move_s_6 = create_grid_image(green_blob_move_6_xpm, 0, 2 - 32 + 21);
    struct GridImage *green_blob_move_s_7 = create_grid_image(green_blob_move_7_xpm, 0, 2 - 32 + 25);
    struct GridImage *green_blob_move_s_8 = create_grid_image(green_blob_move_8_xpm, 0, 2 - 32 + 30);
    struct GridImage *green_blob_move_sprites_copy[NUM_OF_GREEN_BLOB_DIRECTIONS][NUM_OF_GREEN_BLOB_MOVE_SPRITES] = {{green_blob_move_e_1, green_blob_move_e_2, green_blob_move_e_3, green_blob_move_e_4, green_blob_move_e_5, green_blob_move_e_6, green_blob_move_e_7, green_blob_move_e_8},
                                                                                                                    {green_blob_move_n_1, green_blob_move_n_2, green_blob_move_n_3, green_blob_move_n_4, green_blob_move_n_5, green_blob_move_n_6, green_blob_move_n_7, green_blob_move_n_8},
                                                                                                                    {green_blob_move_w_1, green_blob_move_w_2, green_blob_move_w_3, green_blob_move_w_4, green_blob_move_w_5, green_blob_move_w_6, green_blob_move_w_7, green_blob_move_w_8},
                                                                                                                    {green_blob_move_s_1, green_blob_move_s_2, green_blob_move_s_3, green_blob_move_s_4, green_blob_move_s_5, green_blob_move_s_6, green_blob_move_s_7, green_blob_move_s_8}};

    memcpy(&green_blob_move_sprites[0][0], &green_blob_move_sprites_copy[0][0], sizeof(struct GridImage *) * NUM_OF_GREEN_BLOB_DIRECTIONS * NUM_OF_GREEN_BLOB_MOVE_SPRITES);

    xpm_image_t *green_blob_death_1_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *green_blob_death_2_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *green_blob_death_3_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *green_blob_death_4_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *green_blob_death_5_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *green_blob_death_6_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *green_blob_death_7_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *green_blob_death_8_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *green_blob_death_9_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "green_blob_death_1.xpm"), green_blob_death_1_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "green_blob_death_2.xpm"), green_blob_death_2_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "green_blob_death_3.xpm"), green_blob_death_3_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "green_blob_death_4.xpm"), green_blob_death_4_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "green_blob_death_5.xpm"), green_blob_death_5_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "green_blob_death_6.xpm"), green_blob_death_6_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "green_blob_death_7.xpm"), green_blob_death_7_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "green_blob_death_8.xpm"), green_blob_death_8_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "green_blob_death_9.xpm"), green_blob_death_9_xpm);
    struct GridImage *green_blob_death_1 = create_grid_image(green_blob_death_1_xpm, 0, 2);
    struct GridImage *green_blob_death_2 = create_grid_image(green_blob_death_2_xpm, 0, 2);
    struct GridImage *green_blob_death_3 = create_grid_image(green_blob_death_3_xpm, 0, 2);
    struct GridImage *green_blob_death_4 = create_grid_image(green_blob_death_4_xpm, 0, 2);
    struct GridImage *green_blob_death_5 = create_grid_image(green_blob_death_5_xpm, 0, 2);
    struct GridImage *green_blob_death_6 = create_grid_image(green_blob_death_6_xpm, 0, 2);
    struct GridImage *green_blob_death_7 = create_grid_image(green_blob_death_7_xpm, 0, 2);
    struct GridImage *green_blob_death_8 = create_grid_image(green_blob_death_8_xpm, 0, 2);
    struct GridImage *green_blob_death_9 = create_grid_image(green_blob_death_9_xpm, 0, 2);
    struct GridImage *green_blob_death_sprites_copy[NUM_OF_GREEN_BLOB_DEATH_SPRITES] = {green_blob_death_1, green_blob_death_2, green_blob_death_3, green_blob_death_4, green_blob_death_5, green_blob_death_6, green_blob_death_7, green_blob_death_8, green_blob_death_9};
    memcpy(&green_blob_death_sprites[0], &green_blob_death_sprites_copy[0], sizeof(struct GridImage *) * NUM_OF_GREEN_BLOB_DEATH_SPRITES);

    xpm_image_t *green_blob_attack_e_n_1_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *green_blob_attack_e_n_2_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *green_blob_attack_e_n_3_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *green_blob_attack_e_n_4_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *green_blob_attack_e_n_5_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "green_blob_attack_e_n_1.xpm"), green_blob_attack_e_n_1_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "green_blob_attack_e_n_2.xpm"), green_blob_attack_e_n_2_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "green_blob_attack_e_n_3.xpm"), green_blob_attack_e_n_3_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "green_blob_attack_e_n_4.xpm"), green_blob_attack_e_n_4_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "green_blob_attack_e_n_5.xpm"), green_blob_attack_e_n_5_xpm);
    struct GridImage *green_blob_attack_e_1 = create_grid_image(green_blob_attack_e_n_1_xpm, 0, 2);
    struct GridImage *green_blob_attack_e_2 = create_grid_image(green_blob_attack_e_n_2_xpm, 3, 2);
    struct GridImage *green_blob_attack_e_3 = create_grid_image(green_blob_attack_e_n_3_xpm, 6, 2);
    struct GridImage *green_blob_attack_e_4 = create_grid_image(green_blob_attack_e_n_4_xpm, 9, 2);
    struct GridImage *green_blob_attack_e_5 = create_grid_image(green_blob_attack_e_n_5_xpm, 12, 2);
    struct GridImage *green_blob_attack_n_1 = create_grid_image(green_blob_attack_e_n_1_xpm, 0, 2);
    struct GridImage *green_blob_attack_n_2 = create_grid_image(green_blob_attack_e_n_2_xpm, 0, -1);
    struct GridImage *green_blob_attack_n_3 = create_grid_image(green_blob_attack_e_n_3_xpm, 0, -4);
    struct GridImage *green_blob_attack_n_4 = create_grid_image(green_blob_attack_e_n_4_xpm, 0, -7);
    struct GridImage *green_blob_attack_n_5 = create_grid_image(green_blob_attack_e_n_5_xpm, 0, -10);

    xpm_image_t *green_blob_attack_w_s_1_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *green_blob_attack_w_s_2_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *green_blob_attack_w_s_3_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *green_blob_attack_w_s_4_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *green_blob_attack_w_s_5_xpm = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "green_blob_attack_w_s_1.xpm"), green_blob_attack_w_s_1_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "green_blob_attack_w_s_2.xpm"), green_blob_attack_w_s_2_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "green_blob_attack_w_s_3.xpm"), green_blob_attack_w_s_3_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "green_blob_attack_w_s_4.xpm"), green_blob_attack_w_s_4_xpm);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "green_blob_attack_w_s_5.xpm"), green_blob_attack_w_s_5_xpm);
    struct GridImage *green_blob_attack_w_1 = create_grid_image(green_blob_attack_w_s_1_xpm, 0, 2);
    struct GridImage *green_blob_attack_w_2 = create_grid_image(green_blob_attack_w_s_2_xpm, -3, 2);
    struct GridImage *green_blob_attack_w_3 = create_grid_image(green_blob_attack_w_s_3_xpm, -6, 2);
    struct GridImage *green_blob_attack_w_4 = create_grid_image(green_blob_attack_w_s_4_xpm, -9, 2);
    struct GridImage *green_blob_attack_w_5 = create_grid_image(green_blob_attack_w_s_5_xpm, -12, 2);
    struct GridImage *green_blob_attack_s_1 = create_grid_image(green_blob_attack_w_s_1_xpm, 0, 2);
    struct GridImage *green_blob_attack_s_2 = create_grid_image(green_blob_attack_w_s_2_xpm, 0, 5);
    struct GridImage *green_blob_attack_s_3 = create_grid_image(green_blob_attack_w_s_3_xpm, 0, 8);
    struct GridImage *green_blob_attack_s_4 = create_grid_image(green_blob_attack_w_s_4_xpm, 0, 11);
    struct GridImage *green_blob_attack_s_5 = create_grid_image(green_blob_attack_w_s_5_xpm, 0, 14);

    struct GridImage *green_blob_attack_sprites_copy[NUM_OF_GREEN_BLOB_DIRECTIONS][NUM_OF_GREEN_BLOB_ATTACK_SPRITES] = {{green_blob_attack_e_1, green_blob_attack_e_2, green_blob_attack_e_3, green_blob_attack_e_4, green_blob_attack_e_5},
                                                                                                                        {green_blob_attack_n_1, green_blob_attack_n_2, green_blob_attack_n_3, green_blob_attack_n_4, green_blob_attack_n_5},
                                                                                                                        {green_blob_attack_w_1, green_blob_attack_w_2, green_blob_attack_w_3, green_blob_attack_w_4, green_blob_attack_w_5},
                                                                                                                        {green_blob_attack_s_1, green_blob_attack_s_2, green_blob_attack_s_3, green_blob_attack_s_4, green_blob_attack_s_5}};
    memcpy(&green_blob_attack_sprites[0][0], &green_blob_attack_sprites_copy[0][0], sizeof(struct GridImage *) * NUM_OF_GREEN_BLOB_DIRECTIONS * NUM_OF_GREEN_BLOB_ATTACK_SPRITES);
    //~https://opengameart.org/content/blob-sprite

    //ORIGINAL ART
    spearman_special_e_w = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    spearman_special_n_s = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_special_e_w.xpm"), spearman_special_e_w);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_special_n_s.xpm"), spearman_special_n_s);
    //~ORIGINAL ART
}

void generate_UI_sprites(char *path)
{
    //https://opengameart.org/content/hearthealth
    UI_full_heart = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    UI_empty_heart = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "UI_full_heart.xpm"), UI_full_heart);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "UI_empty_heart.xpm"), UI_empty_heart);
    //~https://opengameart.org/content/hearthealth

    //https://opengameart.org/content/dwarven-cursor
    mouse_cursor = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "mouse_cursor.xpm"), mouse_cursor);
    //~https://opengameart.org/content/dwarven-cursor

    //ORIGINAL ART
    special_range_border = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    special_range_selected_border = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "special_range_border.xpm"), special_range_border);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "special_range_selected_border.xpm"), special_range_selected_border);
    //ORIGINAL ART

    //https://opengameart.org/content/radial-lightning-effect
    spearman_special_UI = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "spearman_special_UI.xpm"), spearman_special_UI);
    //~https://opengameart.org/content/radial-lightning-effect

    //https://opengameart.org/content/16-bit-gilded-bitmap-font-with-lower-cases
    xpm_image_t *A = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *B = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *C = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *D = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *E = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *F = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *G = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *H = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *I = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *J = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *K = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *L = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *M = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *N = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *O = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *P = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *Q = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *R = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *S = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *T = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *U = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *V = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *W = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *X = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *Y = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_image_t *Z = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    comma = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    final_stop = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    exclamation_mark = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    question_mark = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    one = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    zero = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "A.xpm"), A);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "B.xpm"), B);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "C.xpm"), C);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "D.xpm"), D);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "E.xpm"), E);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "F.xpm"), F);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "G.xpm"), G);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "H.xpm"), H);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "I.xpm"), I);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "J.xpm"), J);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "K.xpm"), K);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "L.xpm"), L);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "M.xpm"), M);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "N.xpm"), N);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "O.xpm"), O);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "P.xpm"), P);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "Q.xpm"), Q);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "R.xpm"), R);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "S.xpm"), S);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "T.xpm"), T);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "U.xpm"), U);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "V.xpm"), V);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "W.xpm"), W);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "X.xpm"), X);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "Y.xpm"), Y);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "Z.xpm"), Z);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "comma.xpm"), comma);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "question_mark.xpm"), question_mark);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "final_stop.xpm"), final_stop);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "!.xpm"), exclamation_mark);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "0.xpm"), zero);
    strcpy(cpy_buff, path);
    file_to_xpm(strcat(cpy_buff, "1.xpm"), one);
    xpm_image_t *upper_letters_copy[NUM_OF_LETTERS] = {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z};
    memcpy(&upper_letters[0], &upper_letters_copy[0], sizeof(xpm_image_t *) * NUM_OF_LETTERS);
    //~https://opengameart.org/content/16-bit-gilded-bitmap-font-with-lower-cases

    //https://unsplash.com/photos/8BgmKIuQ-GU
    menu_background = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    enum xpm_image_type type = XPM_8_8_8_8;
    xpm_load((xpm_map_t)menu_background_xpm, type, menu_background);
    //~https://unsplash.com/photos/8BgmKIuQ-GU

    //https://unsplash.com/photos/5vV1xgPPdoI
    winning_background = (xpm_image_t *)malloc(sizeof(xpm_image_t));
    xpm_load((xpm_map_t)winning_background_xpm, type, winning_background);
    //~https://unsplash.com/photos/5vV1xgPPdoI
}

void sprite_cleanup()
{
    for (int i = 0; i < NUM_OF_SPEARMAN_DIRECTIONS; i++)
    {
        free(spearman_direction_sprites[i]->image);
        free(spearman_direction_sprites[i]);
        for (int j = 0; j < NUM_OF_SPEARMAN_MOVE_SPRITES; j++)
        {
            free(spearman_walk_sprites[i][j]->image);
            free(spearman_walk_sprites[i][j]);
        }
        for (int k = 0; k < NUM_OF_SPEARMAN_ATTACK_SPRITES; k++)
        {
            free(spearman_attack_sprites[i][k]->image);
            free(spearman_attack_sprites[i][k]);
        }
    }

    for (int i = 0; i < NUM_OF_GREEN_BLOB_IDLE_SPITES; i++)
    {
        free(green_blob_idle_sprites[i]->image);
        free(green_blob_idle_sprites[i]);
    }

    bool first = true;
    for (int i = 0; i < NUM_OF_GREEN_BLOB_DIRECTIONS; i++)
    {
        for (int j = 0; j < NUM_OF_GREEN_BLOB_MOVE_SPRITES; j++)
        {
            if (first)
                free(green_blob_move_sprites[i][j]->image);
            free(green_blob_move_sprites[i][j]);
        }
        first = false;
    }

    for (int i = 0; i < NUM_OF_GREEN_BLOB_DEATH_SPRITES; i++)
    {
        free(green_blob_death_sprites[i]->image);
        free(green_blob_death_sprites[i]);
    }

    for (int i = 0; i < NUM_OF_GREEN_BLOB_DIRECTIONS; i++)
    {
        for (int j = 0; j < NUM_OF_GREEN_BLOB_ATTACK_SPRITES; j++)
        {
            free(green_blob_attack_sprites[i][j]);
            if (i == 0 || i == 2)
                free(green_blob_attack_sprites[i][j]->image);
        }
    }
    for (int i = 0; i < NUM_OF_LETTERS; i++)
    {
        free(upper_letters[i]);
    }
    free(comma);
    free(final_stop);
    free(question_mark);
    free(exclamation_mark);
    free(winning_background);
    free(menu_background);
    free(UI_empty_heart);
    free(UI_full_heart);
    free(mouse_cursor);
    free(special_range_border);
    free(special_range_selected_border);
    free(spearman_special_e_w);
    free(spearman_special_n_s);
    free(spearman_special_UI);
}
