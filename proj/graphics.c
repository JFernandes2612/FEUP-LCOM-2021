#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>
#include <stdio.h>
#include <string.h>
#include "graphics.h"
#include "player.h"
#include "enemies.h"
#include "grid.h"

#define RGB(r, g, b) (r << 16 | g << 8 | b)

#define INVISIBLE 0xFF00DC

#define VBE_FUNC 0x4F
#define SET_VBE_MODE 0x02

#define V_RES_OFFSET_TILES 24

static int *video_mem; /* Process (virtual) address to which VRAM is mapped as 32bit*/
static int *buffer;
static int *background_buffer;

static unsigned h_res;          /* Horizontal resolution in pixels */
static unsigned v_res;          /* Vertical resolution in pixels */
static unsigned bits_per_pixel; /* Number of VRAM bits per pixel */

static const uint8_t tile_size = 32;

struct Cursor *create_cursor()
{
    struct Cursor *c;
    c = malloc(sizeof(*c));
    c->x = 0;
    c->y = 0;
    return c;
}

void update_mouse_position(struct Cursor *c, const int16_t delta_x, const int16_t delta_y)
{
    c->x += delta_x;
    c->y -= delta_y;

    c->x = c->x < 0 ? 0 : c->x;
    c->y = c->y < 0 ? 0 : c->y;

    c->x = c->x > (int16_t)(h_res - mouse_cursor->width) ? (int16_t)(h_res - mouse_cursor->width) : c->x;
    c->y = c->y > (int16_t)(v_res - mouse_cursor->height) ? (int16_t)(v_res - mouse_cursor->height) : c->y;
}

int mouse_grid_pos(struct Cursor *c, uint8_t *x_grid, uint8_t *y_grid)
{
    if (c->x < tile_size || c->x > (int16_t)(h_res - tile_size) || c->y < tile_size * 3 || c->y > (int16_t)(v_res - tile_size * 3 - V_RES_OFFSET_TILES))
        return 1;

    *x_grid = (c->x - tile_size) / tile_size;
    *y_grid = (c->y - tile_size * 3) / tile_size;
    return 0;
}

int paint_cursor(struct Cursor *c)
{
    if (paint_xpm(mouse_cursor, c->x, c->y, false))
        return 1;
    return 0;
}

int create_background()
{
    for (unsigned x = 0; x < h_res; x += tile_size)
    {
        for (unsigned y = 0; y <= v_res - tile_size * 3 - V_RES_OFFSET_TILES; y += tile_size)
        {
            if (x == 0 && y == 0)
            {
                if (paint_xpm(nw_corner, x, y, true))
                    return 1;
            }
            if (x == 0 && y == v_res - tile_size * 3 - V_RES_OFFSET_TILES)
            {
                if (paint_xpm(sw_corner, x, y, true))
                    return 1;
            }
            else if (x == h_res - tile_size && y == v_res - tile_size * 3 - V_RES_OFFSET_TILES)
            {
                if (paint_xpm(se_corner, x, y, true))
                    return 1;
            }
            else if (x == h_res - tile_size && y == 0)
            {
                if (paint_xpm(ne_corner, x, y, true))
                    return 1;
            }
            else if (x == 0 || x == h_res - tile_size)
            {
                //lateral walls will be drawn after all entities
                continue;
            }
            else if (y == 0)
            {
                if (paint_xpm(n_wall_top, x, y, true))
                    return 1;
            }
            else if (y == v_res - tile_size * 3 - V_RES_OFFSET_TILES)
            {
                if (paint_xpm(s_wall, x, y, true))
                    return 1;
            }
            else if (y == tile_size && x == tile_size)
            {
                if (paint_xpm(n_wall_shadow, x, y, true))
                    return 1;
            }
            else if (y == tile_size && x != h_res - tile_size && x != 0)
            {
                if (paint_xpm(n_wall, x, y, true))
                    return 1;
            }
            else if (y == tile_size * 2)
                continue;
            else if (x == tile_size)
            {
                if (paint_xpm(floor_tile_shadow, x, y, true))
                    return 1;
            }
            else
            {
                size_t r = random() % 100 + 1;
                if (r < 85)
                {
                    if (paint_xpm(floor_tile_1, x, y, true))
                        return 1;
                }
                else if (r >= 85 && r < 95)
                {
                    if (paint_xpm(floor_tile_2, x, y, true))
                        return 1;
                }
                else
                {
                    if (paint_xpm(floor_tile_3, x, y, true))
                        return 1;
                }
            }
        }
    }
    if (paint_area(0, v_res - tile_size * 2 - V_RES_OFFSET_TILES, 800, tile_size * 2 + V_RES_OFFSET_TILES, 0x42393A, true))
        return 1;
    return 0;
}

int paint_background_lateral_walls() //buffer
{
    for (unsigned y = tile_size; y <= v_res - tile_size * 4 - V_RES_OFFSET_TILES; y += tile_size)
    {
        if (paint_xpm(e_wall, h_res - tile_size, y, false))
            return 1;
        if (paint_xpm(w_wall, 0, y, false))
            return 1;
    }
    return 0;
}

int paint_grid()
{
    for (uint8_t y = 0; y != GridY; y++)
    {
        for (uint8_t x = 0; x != GridX; x++)
        {
            if (grid[y][x])
            {
                struct Entity *entity = grid[y][x];
                switch (entity->type)
                {
                case SPEARMAN:
                {
                    struct SpearMan *p = (struct SpearMan *)(entity->entity_info);
                    if (paint_xpm(p->current_sprite->image, (x + 1) * tile_size + p->current_sprite->x_offset, (y + 3) * tile_size + p->current_sprite->y_offset, false))
                        return 1;
                    break;
                }
                case GREEN_BLOB:
                {
                    struct GreenBlob *p = (struct GreenBlob *)(entity->entity_info);
                    if (paint_xpm(p->current_sprite->image, (x + 1) * tile_size + p->current_sprite->x_offset, (y + 3) * tile_size + p->current_sprite->y_offset, false))
                        return 1;
                    break;
                }
                default:
                    break;
                }
            }
        }
    }
    return 0;
}

int paint_UI(struct SpearMan *s)
{
    for (uint8_t hp = 0; hp != s->maxHP; hp++)
    {
        if (hp < s->HP)
        {
            if (paint_xpm(UI_full_heart, ((tile_size * 3) / 2) * (hp + 1), v_res - tile_size * 2, false))
                return 1;
        }
        else
        {
            if (paint_xpm(UI_empty_heart, ((tile_size * 3) / 2) * (hp + 1), v_res - tile_size * 2, false))
                return 1;
        }
    }

    if (!s->special_in_cd)
    {
        if (paint_xpm(spearman_special_UI, ((tile_size * 3) / 2) * (s->maxHP + 2), v_res - tile_size * 3 + tile_size / 4, false))
            return 1;
        if (paint_text("Q", ((tile_size * 3) / 2) * (s->maxHP + 2), v_res - tile_size * 3 + tile_size / 4 + spearman_special_UI->height, false))
            return 1;
    }

    if (s->channeling_special)
    {
        for (char x = (char)(s->x - s->special_range); x <= s->x + s->special_range; x++)
        {
            if (x == s->x || x < 0 || x >= GridX)
                continue;
            if (s->target_y == s->y && ((s->target_x >= (char)(s->x - s->special_range) && s->target_x < s->x && x >= (char)(s->x - s->special_range) && x < s->x) || (s->target_x > s->x && s->target_x <= s->x + s->special_range && x > s->x && x <= s->x + s->special_range)))
            {
                if (paint_xpm(special_range_selected_border, (x + 1) * tile_size, (s->y + 3) * tile_size, false))
                    return 1;
                continue;
            }
            if (paint_xpm(special_range_border, (x + 1) * tile_size, (s->y + 3) * tile_size, false))
                return 1;
        }
        for (char y = (char)(s->y - s->special_range); y <= s->y + s->special_range; y++)
        {
            if (y == s->y || y < 0 || y >= GridY)
                continue;
            if (s->target_x == s->x && ((s->target_y >= (char)(s->y - s->special_range) && s->target_y < s->y && y >= (char)(s->y - s->special_range) && y < s->y) || (s->target_y > s->y && s->target_y <= s->y + s->special_range && y > s->y && y <= s->y + s->special_range)))
            {
                if (paint_xpm(special_range_selected_border, (s->x + 1) * tile_size, (y + 3) * tile_size, false))
                    return 1;
                continue;
            }
            if (paint_xpm(special_range_border, (s->x + 1) * tile_size, (y + 3) * tile_size, false))
                return 1;
        }
    }

    return 0;
}

void background_refresh()
{
    buffer = memcpy(buffer, background_buffer, ((bits_per_pixel + 7) / 8) * h_res * v_res);
}

void video_refresh()
{
    video_mem = memcpy(video_mem, buffer, ((bits_per_pixel + 7) / 8) * h_res * v_res);
}

int paint_text(const char* s, const uint16_t x, const uint16_t y, bool background)
{
    for (size_t i = 0; i != strlen(s); i++)
    {
        if (s[i] == ' ')
        {
            continue;
        }
        else if (s[i] == '.')
        {
           if (paint_xpm(final_stop, x + i * final_stop->width, y, background))
            return 1;
        }
        else if (s[i] == '!')
        {
           if (paint_xpm(exclamation_mark, x + i * exclamation_mark->width, y, background))
            return 1;
        }
        else if (s[i] == '?')
        {
           if (paint_xpm(question_mark, x + i * question_mark->width, y, background))
            return 1;
        }
        else if (s[i] == ',')
        {
           if (paint_xpm(comma, x + i * comma->width, y + 5, background))
            return 1;
        }
        else if (s[i] == '0')
        {
            if (paint_xpm(zero, x + i * zero->width, y, background))
                return 1;
        }
        else if (s[i] == '1')
        {
            if (paint_xpm(one, x + i * one->width, y, background))
                return 1;
        }
        else if (paint_xpm(upper_letters[s[i] - 'A'], x + i * upper_letters[s[i] - 'A']->width, y, background))
        {
            return 1;
        }
    }
    return 0;
}

int paint_pixel(const uint16_t x, const uint16_t y, const uint32_t colour, bool background) //char* -> byte a byte. pixel a pixel -> mult por bytes/pixel
{
    if (x >= h_res || y >= v_res)
        return 1;
    if (background)
        *(background_buffer + y * h_res + x) = colour;
    else
        *(buffer + y * h_res + x) = colour;

    return 0;
}

int file_to_xpm(const char *filepath, xpm_image_t *img)
{
    FILE *file = fopen(filepath, "r");
    if (file == NULL)
    {
        return 1;
    }
    char *buff = NULL;
    size_t counter = 0;
    size_t total_size = 0;
    char **xpm = NULL;
    while (!feof(file))
    {
        buff = (char *)malloc(1152); //for our art this should work just fine
        fgets(buff, 1152, file);
        buff = (char *)realloc(buff, strlen(buff));
        for (size_t i = 0; i != strlen(buff); i++)
        {
            if (buff[i] == '\n' || buff[i] == '\r')
            {
                buff[i] = '\0';
                break;
            }
        }
        total_size += strlen(buff);
        xpm = (char **)realloc(xpm, total_size);
        xpm[counter] = buff;
        counter++;
    }
    fclose(file);

    enum xpm_image_type type = XPM_8_8_8_8;
    if (xpm_load((xpm_map_t)(xpm), type, img) == NULL)
        return 2;

    for (size_t i = 0; i != counter; i++)
    {
        free(xpm[i]);
    }
    free(xpm);
    return 0;
}

int paint_xpm(const xpm_image_t *img, const uint16_t start_x, const uint16_t start_y, bool background)
{
    if (start_y + img->height > v_res || start_x + img->width > h_res)
        return 1;

    int byte_number = 0;
    for (uint16_t y = 0; y < img->height; y++)
    {
        for (uint16_t x = 0; x < img->width; x++)
        {
            uint32_t colour = RGB(img->bytes[byte_number + 2], img->bytes[byte_number + 1], img->bytes[byte_number]);
            if (colour != INVISIBLE)
                if (paint_pixel(start_x + x, start_y + y, colour, background))
                    return 1; //does not need any verification since this is done at the start before painting any pixels but better sure than sorry
            byte_number += 4;
        }
    }
    return 0;
}

int paint_area(const uint16_t start_x, const uint16_t start_y, const uint16_t width, const uint16_t height, const uint32_t colour, const bool background)
{
    if (start_y + height > v_res || start_x + width > h_res)
        return 1;
    for (uint16_t y = start_y; y != start_y + height; y++)
    {
        for (uint16_t x = start_x; x != start_x + width; x++)
        {
            if (paint_pixel(x, y, colour, background))
                return 1;
        }
    }
    return 0;
}

int vg_init_ours()
{
    vbe_mode_info_t mode_info;
    vbe_get_mode_info(0x143, &mode_info);
    h_res = mode_info.XResolution;
    v_res = mode_info.YResolution;
    bits_per_pixel = mode_info.BitsPerPixel;
    int vram_size = ((bits_per_pixel + 7) / 8) * h_res * v_res;
    struct minix_mem_range mr;
    mr.mr_base = mode_info.PhysBasePtr;
    mr.mr_limit = mr.mr_base + vram_size;

    int r;

    if (OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr))) //concede privilégios a SELF para adicionar memória
    {
        panic("sys_privctl (ADD_MEM) failed: %d\n", r);
        return 1;
    }

    video_mem = (int *)vm_map_phys(SELF, (void *)mr.mr_base, vram_size); //aloca essa memória

    if (video_mem == MAP_FAILED)
    {
        panic("couldn't map video memory");
        return 1;
    }

    struct reg86 r86;
    memset(&r86, 0, sizeof(r86)); /* zero the structure */
    r86.intno = 0x10;
    r86.ah = VBE_FUNC;
    r86.al = SET_VBE_MODE;
    r86.bx = 0x143 | BIT(14);
    if (sys_int86(&r86) != OK)
    {
        panic("\tvg_init_ours(): sys_int86() failed \n");
        return 1;
    }
    buffer = (int *)malloc(vram_size);
    background_buffer = (int *)malloc(vram_size);
    return 0;
}

int vg_exit_ours()
{
    free(video_mem);
    free(buffer);
    free(background_buffer);
    return vg_exit();
}
