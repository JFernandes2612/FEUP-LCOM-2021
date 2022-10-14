#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>

#include "entities.h"
#include "enemies.h"
#include "player.h"
#include "grid.h"

int grid_move(const uint8_t curr_x, const uint8_t curr_y, const uint8_t new_x, const uint8_t new_y)
{
    if (new_x >= GridX || new_y >= GridY)
        return 1;
    if (grid[new_y][new_x])
        return 2;
    grid[new_y][new_x] = grid[curr_y][curr_x];
    grid[curr_y][curr_x] = NULL;
    return 0;
}

int grid_add(struct Entity *entity)
{
    uint8_t x = 0, y = 0;
    switch (entity->type)
    {
    case SPEARMAN:
        x = ((struct SpearMan *)entity->entity_info)->x;
        y = ((struct SpearMan *)entity->entity_info)->y;
        break;
    case GREEN_BLOB:
        x = ((struct GreenBlob *)entity->entity_info)->x;
        y = ((struct GreenBlob *)entity->entity_info)->y;
        break;
    default:
        break;
    }
    if (x >= GridX || y >= GridY || grid[y][x])
    {
        return 1;
    }
    grid[y][x] = entity;
    return 0;
}

int grid_health_mod(const uint8_t x, const uint8_t y, const char health_mod)
{
    if (x >= GridX || y >= GridY || !grid[y][x])
    {
        return 1;
    }
    struct Entity *entity = grid[y][x];
    switch (entity->type)
    {
    case SPEARMAN:
    {
        struct SpearMan *sp = (struct SpearMan *)entity->entity_info;
        sp->HP += health_mod;
        if (sp->HP <= 0)
        {
            sp->curr_action = SPEARMAN_DEAD;
        }
        break;
    }
    case GREEN_BLOB:
    {
        struct GreenBlob *gb = (struct GreenBlob *)entity->entity_info;
        gb->HP += health_mod;
        if (gb->HP <= 0)
        {
            gb->action = GREEN_BLOB_DEAD;
        }
        break;
    }
    default:
        break;
    }
    return 0;
}

int update_animations(const uint32_t frame)
{
    bool dead = false;
    struct Entity *entity;
    for (uint8_t y = 0; y < GridY; y++)
    {
        for (uint8_t x = 0; x < GridX; x++)
        {
            entity = grid[y][x];
            if (entity == 0)
                continue;
            switch (entity->type)
            {
            case SPEARMAN:
                dead = animate_spearman((struct SpearMan *)entity->entity_info, frame);
                if (dead)
                    return 1;
                break;
            case GREEN_BLOB:
                animate_green_blob((struct GreenBlob *)entity->entity_info, frame);
                break;
            default:
                break;
            }
        }
    }
    return dead;
}

void delete_grid()
{
    struct Entity *entity;
    for (uint8_t y = 0; y < GridY; y++)
    {
        for (uint8_t x = 0; x < GridX; x++)
        {
            entity = grid[y][x];
            if (entity == 0)
                continue;
            free(entity->entity_info);
            free(entity);
            grid[y][x] = 0;
        }
    }
}
