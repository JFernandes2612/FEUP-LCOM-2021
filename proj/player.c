#include <lcom/lcf.h>
#include <lcom/liblm.h>
#include <lcom/proj.h>
#include "player.h"
#include "rtc.h"
#include "graphics.h"

#define ATTACK_NUM_OF_FRAMES 3
#define MOVE_NUM_OF_FRAMES 4
#define DEATH_NUM_OF_FRAMES 4

struct Entity *create_spearman(const uint8_t x, const uint8_t y)
{
    struct SpearMan *spearman;
    spearman = (struct SpearMan *)malloc(sizeof(*spearman));
    spearman->HP = 5;
    spearman->maxHP = 5;
    spearman->dmg = 2;
    spearman->special_in_cd = false;
    spearman->special_cd = 20;
    spearman->special_range = 5;
    spearman->channeling_special = false;
    spearman->special_dmg = 10;
    spearman->x = x;
    spearman->y = y;
    spearman->curr_action = SPEARMAN_NO_ACT;
    spearman->current_sprite = spearman_direction_sprites[0];
    spearman->d = RIGHT;
    spearman->target_x = 0;
    spearman->target_x = 0;
    struct Entity *spearman_entity;
    spearman_entity = (struct Entity *)malloc(sizeof(*spearman_entity));
    spearman_entity->entity_info = spearman;
    spearman_entity->type = SPEARMAN;
    return spearman_entity;
}

int spearman_attack(struct SpearMan *spearman)
{
    short x_attack = 0, y_attack = 0;
    switch (spearman->d)
    {
    case RIGHT:
        x_attack++;
        break;
    case UP:
        y_attack--;
        break;
    case LEFT:
        x_attack--;
        break;
    case DOWN:
        y_attack++;
        break;
    }
    return grid_health_mod(spearman->x + x_attack, spearman->y + y_attack, -spearman->dmg);
}

int spearman_move(struct SpearMan *spearman, const enum Direction direction)
{
    short delta_x = 0, delta_y = 0;
    spearman->d = direction;
    spearman->current_sprite = spearman_direction_sprites[spearman->d];
    switch (direction)
    {
    case RIGHT:
        delta_x++;
        break;
    case UP:
        delta_y--;
        break;
    case LEFT:
        delta_x--;
        break;
    case DOWN:
        delta_y++;
        break;
    }
    if (grid_move(spearman->x, spearman->y, spearman->x + delta_x, spearman->y + delta_y) == 0)
    {
        spearman->x += delta_x;
        spearman->y += delta_y;
    }
    else
        return 1;
    return 0;
}

int spearman_act(struct SpearMan *spearman, enum SpearmanAction PA)
{
    if (spearman->curr_action == SPEARMAN_DEAD)
        return 2;
    spearman->curr_action = PA;
    switch (PA)
    {
    case SPEARMAN_MOVE_DOWN:
    case SPEARMAN_MOVE_UP:
    case SPEARMAN_MOVE_LEFT:
    case SPEARMAN_MOVE_RIGHT:
        if (spearman_move(spearman, (enum Direction)spearman->curr_action))
        {
            spearman->curr_action = SPEARMAN_NO_ACT;
            return 1;
        }
        break;
    case SPEARMAN_ATTACK:
        if (spearman_attack(spearman))
        {
            spearman->curr_action = SPEARMAN_NO_ACT;
            return 1;
        }
        break;
    case SPEARMAN_SPECIAL_DOWN:
    case SPEARMAN_SPECIAL_UP:
    case SPEARMAN_SPECIAL_LEFT:
    case SPEARMAN_SPECIAL_RIGHT:
        if (spearman_special(spearman))
        {
            spearman->curr_action = SPEARMAN_NO_ACT;
            return 1;
        }
        spearman->channeling_special = false;
        break;
    default:
        spearman->curr_action = SPEARMAN_NO_ACT;
        return 1;
    }
    return 0;
}

int spearman_special(struct SpearMan *spearman)
{
    if (spearman->curr_action == SPEARMAN_SPECIAL_RIGHT)
    {
        spearman->current_sprite = spearman_direction_sprites[0];
        spearman->d = RIGHT;
        for (uint8_t x = spearman->x + 1; x <= spearman->x + spearman->special_range; x++)
        {
            grid_health_mod(x, spearman->y, (char)(-spearman->special_dmg));
        }
    }
    else if (spearman->curr_action == SPEARMAN_SPECIAL_LEFT)
    {
        spearman->current_sprite = spearman_direction_sprites[2];
        spearman->d = LEFT;
        for (uint8_t x = spearman->x - 1; x >= spearman->x - spearman->special_range; x--)
        {
            grid_health_mod(x, spearman->y, (char)(-spearman->special_dmg));
            if (x == 0)
                break;
        }
    }
    else if (spearman->curr_action == SPEARMAN_SPECIAL_DOWN)
    {
        spearman->current_sprite = spearman_direction_sprites[3];
        spearman->d = DOWN;
        for (uint8_t y = spearman->y + 1; y <= spearman->y + spearman->special_range; y++)
        {
            grid_health_mod(spearman->x, y, (char)(-spearman->special_dmg));
        }
    }
    else if (spearman->curr_action == SPEARMAN_SPECIAL_UP)
    {
        spearman->current_sprite = spearman_direction_sprites[1];
        spearman->d = UP;
        for (uint8_t y = spearman->y - 1; y >= spearman->y - spearman->special_range; y--)
        {
            grid_health_mod(spearman->x, y, (char)(-spearman->special_dmg));
            if (y == 0)
                break;
        }
    }

    if (spearman->channeling_special)
    {
        spearman->special_in_cd = true;
        rtc_set_alarm_delta_s(spearman->special_cd);
    }

    return 0;
}

int animate_spearman(struct SpearMan *spearman, const uint32_t frame)
{
    switch (spearman->curr_action)
    {
    case SPEARMAN_MOVE_UP:
    case SPEARMAN_MOVE_DOWN:
    case SPEARMAN_MOVE_LEFT:
    case SPEARMAN_MOVE_RIGHT:
        animate_spearman_move(spearman, frame);
        break;
    case SPEARMAN_ATTACK:
        animate_spearman_attack(spearman, frame);
        break;
    case SPEARMAN_DEAD:
        if (animate_spearman_death(spearman, frame))
            return 1;
        break;
    case SPEARMAN_SPECIAL_UP:
    case SPEARMAN_SPECIAL_DOWN:
    case SPEARMAN_SPECIAL_LEFT:
    case SPEARMAN_SPECIAL_RIGHT:
        animate_spearman_special(spearman, frame);
        break;
    default:
        break;
    }
    return 0;
}

void animate_spearman_special(struct SpearMan *spearman, const uint32_t frame)
{
    switch (frame % sys_hz()) //change the current sprite to the apripriate one at the right time
    {
    case 0:
        spearman->current_sprite = spearman_attack_sprites[spearman->d][0];
        break;
    case ATTACK_NUM_OF_FRAMES:
        spearman->current_sprite = spearman_attack_sprites[spearman->d][1];
        break;
    case ATTACK_NUM_OF_FRAMES * 2:
        spearman->current_sprite = spearman_attack_sprites[spearman->d][2];
        break;
    case ATTACK_NUM_OF_FRAMES * 3:
        spearman->current_sprite = spearman_attack_sprites[spearman->d][3];
        break;
    case ATTACK_NUM_OF_FRAMES * 4:
        spearman->current_sprite = spearman_attack_sprites[spearman->d][4];
        break;
    case ATTACK_NUM_OF_FRAMES * 5:
        spearman->current_sprite = spearman_attack_sprites[spearman->d][5];
        break;
    //RAY
    case ATTACK_NUM_OF_FRAMES * 7:
        spearman->current_sprite = spearman_attack_sprites[spearman->d][6];
        break;
    case ATTACK_NUM_OF_FRAMES * 8:
        spearman->current_sprite = spearman_attack_sprites[spearman->d][7];
        break;
    case ATTACK_NUM_OF_FRAMES * 9: //animation ended - reset state
        spearman->current_sprite = spearman_direction_sprites[spearman->d];
        spearman->curr_action = SPEARMAN_NO_ACT;
        break;
    default:
    {
        if (frame % sys_hz() > ATTACK_NUM_OF_FRAMES * 5 && frame % sys_hz() < ATTACK_NUM_OF_FRAMES * 7)
        {
            if (spearman->d == RIGHT)
            {
                for (uint8_t x = spearman->x + 1; x <= spearman->x + spearman->special_range; x++)
                {
                    if (paint_xpm(spearman_special_e_w, (x + 1) * 32, (spearman->y + 3) * 32, false))
                        return;
                }
            }
            else if (spearman->d == LEFT)
            {
                for (uint8_t x = spearman->x - 1; x >= spearman->x - spearman->special_range; x--)
                {
                    if (paint_xpm(spearman_special_e_w, (x + 1) * 32, (spearman->y + 3) * 32, false))
                        return;
                    if (x == 0)
                        break;
                }
            }
            else if (spearman->d == DOWN)
            {
                for (uint8_t y = spearman->y + 1; y <= spearman->y + spearman->special_range; y++)
                {
                    if (paint_xpm(spearman_special_n_s, (spearman->x + 1) * 32, (y + 3) * 32, false))
                        return;
                }
            }
            else if (spearman->d == UP)
            {
                for (uint8_t y = spearman->y - 1; y >= spearman->y - spearman->special_range; y--)
                {
                    if (paint_xpm(spearman_special_n_s, (spearman->x + 1) * 32, (y + 3) * 32, false))
                        return;
                    if (y == 0)
                        break;
                }
            }
        }
        break;
    }
    }
}

void animate_spearman_attack(struct SpearMan *spearman, const uint32_t frame)
{
    switch (frame % sys_hz()) //change the current sprite to the apripriate one at the right time
    {
    case 0:
        spearman->current_sprite = spearman_attack_sprites[spearman->d][0];
        break;
    case ATTACK_NUM_OF_FRAMES:
        spearman->current_sprite = spearman_attack_sprites[spearman->d][1];
        break;
    case ATTACK_NUM_OF_FRAMES * 2:
        spearman->current_sprite = spearman_attack_sprites[spearman->d][2];
        break;
    case ATTACK_NUM_OF_FRAMES * 3:
        spearman->current_sprite = spearman_attack_sprites[spearman->d][3];
        break;
    case ATTACK_NUM_OF_FRAMES * 4:
        spearman->current_sprite = spearman_attack_sprites[spearman->d][4];
        break;
    case ATTACK_NUM_OF_FRAMES * 5:
        spearman->current_sprite = spearman_attack_sprites[spearman->d][5];
        break;
    case ATTACK_NUM_OF_FRAMES * 6:
        spearman->current_sprite = spearman_attack_sprites[spearman->d][6];
        break;
    case ATTACK_NUM_OF_FRAMES * 7:
        spearman->current_sprite = spearman_attack_sprites[spearman->d][7];
        break;
    case ATTACK_NUM_OF_FRAMES * 8: //animation ended - reset state
        spearman->current_sprite = spearman_direction_sprites[spearman->d];
        spearman->curr_action = SPEARMAN_NO_ACT;
        break;
    default:
        break;
    }
}

void animate_spearman_move(struct SpearMan *spearman, const uint32_t frame)
{
    switch ((frame % sys_hz())) //change the current sprite to the apripriate one at the right time
    {
    case 0:
        spearman->current_sprite = spearman_walk_sprites[spearman->d][0];
        break;
    case MOVE_NUM_OF_FRAMES:
        spearman->current_sprite = spearman_walk_sprites[spearman->d][1];
        break;
    case MOVE_NUM_OF_FRAMES * 2:
        spearman->current_sprite = spearman_walk_sprites[spearman->d][2];
        break;
    case MOVE_NUM_OF_FRAMES * 3:
        spearman->current_sprite = spearman_walk_sprites[spearman->d][3];
        break;
    case MOVE_NUM_OF_FRAMES * 4:
        spearman->current_sprite = spearman_walk_sprites[spearman->d][4];
        break;
    case MOVE_NUM_OF_FRAMES * 5:
        spearman->current_sprite = spearman_walk_sprites[spearman->d][5];
        break;
    case MOVE_NUM_OF_FRAMES * 6:
        spearman->current_sprite = spearman_walk_sprites[spearman->d][6];
        break;
    case MOVE_NUM_OF_FRAMES * 7:
        spearman->current_sprite = spearman_walk_sprites[spearman->d][7];
        break;
    case MOVE_NUM_OF_FRAMES * 8:
        spearman->current_sprite = spearman_walk_sprites[spearman->d][8];
        break;
    case MOVE_NUM_OF_FRAMES * 9:
        spearman->current_sprite = spearman_walk_sprites[spearman->d][9];
        break;
    case MOVE_NUM_OF_FRAMES * 10: //animation ended - reset state
        spearman->current_sprite = spearman_direction_sprites[spearman->d];
        spearman->curr_action = SPEARMAN_NO_ACT;
        break;
    default:
        break;
    }
}

int animate_spearman_death(struct SpearMan *spearman, const uint32_t frame)
{
    switch ((frame % sys_hz())) //change the current sprite to the appropriate one at the right time
    {
    case 30:
        spearman->current_sprite = spearman_death_sprites[spearman->d][0];
        break;
    case 30 + DEATH_NUM_OF_FRAMES:
        spearman->current_sprite = spearman_death_sprites[spearman->d][1];
        break;
    case 30 + DEATH_NUM_OF_FRAMES * 2:
        spearman->current_sprite = spearman_death_sprites[spearman->d][2];
        break;
    case 30 + DEATH_NUM_OF_FRAMES * 3:
        spearman->current_sprite = spearman_death_sprites[spearman->d][3];
        break;
    case 30 + DEATH_NUM_OF_FRAMES * 4:
        spearman->current_sprite = spearman_death_sprites[spearman->d][4];
        break;
    case 30 + DEATH_NUM_OF_FRAMES * 5:
        spearman->current_sprite = spearman_death_sprites[spearman->d][5];
        break;
    case 30 + DEATH_NUM_OF_FRAMES * 6:
        spearman->current_sprite = spearman_death_sprites[spearman->d][6];
        break;
    case 30 + DEATH_NUM_OF_FRAMES * 7:
        spearman->current_sprite = spearman_death_sprites[spearman->d][7];
        break;
    case (30 + DEATH_NUM_OF_FRAMES * 8) % 60: //overflow
        return 1;
    default:
        break;
    }
    return 0;
}
