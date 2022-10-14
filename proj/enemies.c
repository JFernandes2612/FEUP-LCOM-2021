#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>
#include "enemies.h"
#include "grid.h"

#define GREEN_BLOB_IDLE_NUMBER_OF_FRAMES 12
#define GREEN_BLOB_MOVE_NUMBER_OF_FRAMES 5
#define GREEN_BLOB_DEATH_NUMBER_OF_FRAMES 3
#define GREEN_BLOB_ATTACK_NUMBER_OF_FRAMES 3

struct Entity *create_g_blob(uint8_t x, uint8_t y, enum Direction movement)
{
    struct GreenBlob *g_blob;
    g_blob = (struct GreenBlob *)malloc(sizeof(*g_blob));
    g_blob->HP = 1;
    g_blob->dmg = 1;
    g_blob->x = x;
    g_blob->y = y;
    g_blob->direction = movement;
    g_blob->current_sprite = green_blob_idle_sprites[0];
    g_blob->action = GREEN_BLOB_NO_ACT;
    struct Entity *green_blob_entity;
    green_blob_entity = (struct Entity *)malloc(sizeof(*green_blob_entity));
    green_blob_entity->entity_info = g_blob;
    green_blob_entity->type = GREEN_BLOB;
    return green_blob_entity;
}

int green_blob_act(struct GreenBlob *green_blob)
{
    if (green_blob->action == GREEN_BLOB_DEAD)
        return 2;
    short delta_x = 0, delta_y = 0;
    switch (green_blob->direction)
    {
    case RIGHT:
        delta_x++;
        green_blob->action = GREEN_BLOB_MOVE_RIGHT;
        break;
    case UP:
        delta_y--;
        green_blob->action = GREEN_BLOB_MOVE_UP;
        break;
    case LEFT:
        delta_x--;
        green_blob->action = GREEN_BLOB_MOVE_LEFT;
        break;
    case DOWN:
        delta_y++;
        green_blob->action = GREEN_BLOB_MOVE_DOWN;
        break;
    default:
        return 1;
    }
    switch (grid_move(green_blob->x, green_blob->y, green_blob->x + delta_x, green_blob->y + delta_y))
    {
    case 0:
        green_blob->x += delta_x;
        green_blob->y += delta_y;
        green_blob->direction = (green_blob->direction + 1) % 4;
        break;
    case 1:
        green_blob->direction = (green_blob->direction + 1) % 4;
        green_blob->action = GREEN_BLOB_NO_ACT;
        break;
    case 2:
        if (grid[green_blob->y + delta_y][green_blob->x + delta_x]->type != SPEARMAN)
        {
            green_blob->direction = (green_blob->direction + 1) % 4;
            green_blob->action = GREEN_BLOB_NO_ACT;
            break;
        }
        green_blob->action = GREEN_BLOB_ATTACK;
        grid_health_mod(green_blob->x + delta_x, green_blob->y + delta_y, -green_blob->dmg);
        break;
    default:
        return 1;
    }
    return 0;
}

int grid_enemies_move()
{
    struct Entity *entity;
    struct Entity *grid_cpy[GridY][GridX];
    bool moved = false;
    memcpy(&grid_cpy[0][0], &grid[0][0], sizeof(struct Entity *) * GridX * GridY);
    for (uint8_t y = 0; y < GridY; y++)
    {
        for (uint8_t x = 0; x < GridX; x++)
        {
            entity = grid_cpy[y][x];
            if (entity == 0)
                continue;
            switch (entity->type)
            {
            case GREEN_BLOB:
            {
                struct GreenBlob *gb = (struct GreenBlob *)entity->entity_info;
                green_blob_act(gb);
                moved = true;
                break;
            }
            default:
                break;
            }
        }
    }
    return !moved;
}

void animate_green_blob(struct GreenBlob *gb, const uint32_t frame) //this function only runs after the 30th frame until the 90th frame
{
    switch (gb->action)
    {
    case GREEN_BLOB_MOVE_UP:
    case GREEN_BLOB_MOVE_DOWN:
    case GREEN_BLOB_MOVE_LEFT:
    case GREEN_BLOB_MOVE_RIGHT:
        animate_green_blob_move(gb, frame);
        break;
    case GREEN_BLOB_NO_ACT:
        animate_green_blob_idle(gb, frame);
        break;
    case GREEN_BLOB_DEAD:
        animate_green_blob_death(gb, frame);
        break;
    case GREEN_BLOB_ATTACK:
        animate_green_blob_attack(gb, frame);
    default:
        break;
    }
}

void animate_green_blob_idle(struct GreenBlob *gb, const uint32_t frame)
{
    switch ((frame % sys_hz()) % (GREEN_BLOB_IDLE_NUMBER_OF_FRAMES * 4))
    {
    case 0:
        gb->current_sprite = green_blob_idle_sprites[0];
        break;
    case GREEN_BLOB_IDLE_NUMBER_OF_FRAMES:
        gb->current_sprite = green_blob_idle_sprites[1];
        break;
    case GREEN_BLOB_IDLE_NUMBER_OF_FRAMES * 2:
        gb->current_sprite = green_blob_idle_sprites[2];
        break;
    case GREEN_BLOB_IDLE_NUMBER_OF_FRAMES * 3:
        gb->current_sprite = green_blob_idle_sprites[3];
        break;
    default:
        break;
    }
}

void animate_green_blob_move(struct GreenBlob *gb, const uint32_t frame)
{
    switch (frame % sys_hz())
    {
    case 30:
        gb->current_sprite = green_blob_move_sprites[gb->action][0];
        break;
    case 30 + GREEN_BLOB_MOVE_NUMBER_OF_FRAMES:
        gb->current_sprite = green_blob_move_sprites[gb->action][1];
        break;
    case 30 + GREEN_BLOB_MOVE_NUMBER_OF_FRAMES * 2:
        gb->current_sprite = green_blob_move_sprites[gb->action][2];
        break;
    case 30 + GREEN_BLOB_MOVE_NUMBER_OF_FRAMES * 3:
        gb->current_sprite = green_blob_move_sprites[gb->action][3];
        break;
    case 30 + GREEN_BLOB_MOVE_NUMBER_OF_FRAMES * 4:
        gb->current_sprite = green_blob_move_sprites[gb->action][4];
        break;
    case 30 + GREEN_BLOB_MOVE_NUMBER_OF_FRAMES * 5:
        gb->current_sprite = green_blob_move_sprites[gb->action][5];
        break;
    case (30 + GREEN_BLOB_MOVE_NUMBER_OF_FRAMES * 6) % 60: //overflow
        gb->current_sprite = green_blob_move_sprites[gb->action][6];
        break;
    case (30 + GREEN_BLOB_MOVE_NUMBER_OF_FRAMES * 7) % 60: //overflow
        gb->current_sprite = green_blob_move_sprites[gb->action][7];
        break;
    case (30 + GREEN_BLOB_MOVE_NUMBER_OF_FRAMES * 8) % 60: //overflow
        gb->current_sprite = green_blob_idle_sprites[0];
        gb->action = GREEN_BLOB_NO_ACT;
        break;
    default:
        break;
    }
}

void animate_green_blob_death(struct GreenBlob *gb, const uint32_t frame)
{
    switch (frame % sys_hz())
    {
    case 0:
        gb->current_sprite = green_blob_death_sprites[0];
        break;
    case GREEN_BLOB_DEATH_NUMBER_OF_FRAMES:
        gb->current_sprite = green_blob_death_sprites[1];
        break;
    case GREEN_BLOB_DEATH_NUMBER_OF_FRAMES * 2:
        gb->current_sprite = green_blob_death_sprites[2];
        break;
    case GREEN_BLOB_DEATH_NUMBER_OF_FRAMES * 3:
        gb->current_sprite = green_blob_death_sprites[3];
        break;
    case GREEN_BLOB_DEATH_NUMBER_OF_FRAMES * 4:
        gb->current_sprite = green_blob_death_sprites[4];
        break;
    case GREEN_BLOB_DEATH_NUMBER_OF_FRAMES * 5:
        gb->current_sprite = green_blob_death_sprites[5];
        break;
    case GREEN_BLOB_DEATH_NUMBER_OF_FRAMES * 6:
        gb->current_sprite = green_blob_death_sprites[6];
        break;
    case GREEN_BLOB_DEATH_NUMBER_OF_FRAMES * 7:
        gb->current_sprite = green_blob_death_sprites[7];
        break;
    case GREEN_BLOB_DEATH_NUMBER_OF_FRAMES * 8:
        gb->current_sprite = green_blob_death_sprites[8];
        break;
    case GREEN_BLOB_DEATH_NUMBER_OF_FRAMES * 9:
        free(grid[gb->y][gb->x]);
        free(gb);
        grid[gb->y][gb->x] = 0;
        break;
    default:
        break;
    }
}

void animate_green_blob_attack(struct GreenBlob *gb, const uint32_t frame)
{
    switch (frame % sys_hz())
    {
    case 30:
        gb->current_sprite = green_blob_attack_sprites[gb->direction][0];
        break;
    case 30 + GREEN_BLOB_ATTACK_NUMBER_OF_FRAMES:
        gb->current_sprite = green_blob_attack_sprites[gb->direction][1];
        break;
    case 30 + GREEN_BLOB_ATTACK_NUMBER_OF_FRAMES * 2:
        gb->current_sprite = green_blob_attack_sprites[gb->direction][2];
        break;
    case 30 + GREEN_BLOB_ATTACK_NUMBER_OF_FRAMES * 3:
        gb->current_sprite = green_blob_attack_sprites[gb->direction][3];
        break;
    case 30 + GREEN_BLOB_ATTACK_NUMBER_OF_FRAMES * 4:
        gb->current_sprite = green_blob_attack_sprites[gb->direction][4];
        break;
    case 30 + GREEN_BLOB_ATTACK_NUMBER_OF_FRAMES * 5:
        gb->current_sprite = green_blob_attack_sprites[gb->direction][3];
        break;
    case 30 + GREEN_BLOB_ATTACK_NUMBER_OF_FRAMES * 6:
        gb->current_sprite = green_blob_attack_sprites[gb->direction][2];
        break;
    case 30 + GREEN_BLOB_ATTACK_NUMBER_OF_FRAMES * 7:
        gb->current_sprite = green_blob_attack_sprites[gb->direction][1];
        break;
    case 30 + GREEN_BLOB_ATTACK_NUMBER_OF_FRAMES * 8:
        gb->current_sprite = green_blob_attack_sprites[gb->direction][0];
        break;
    case 30 + GREEN_BLOB_ATTACK_NUMBER_OF_FRAMES * 9:
        gb->current_sprite = green_blob_idle_sprites[0];
        gb->action = GREEN_BLOB_NO_ACT;
        break;
    default:
        break;
    }
}
