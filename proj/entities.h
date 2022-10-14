#ifndef ENTITIES_H_
#define ENTITIES_H_

#include <lcom/lcf.h>
#include "sprites/sprites.h"

/**
 * @enum Direction
 * @brief Orientation of an Entity
 */
enum Direction
{
    RIGHT, /**< Right direction (East) */
    UP,    /**< Upwards direction (North) */
    LEFT,  /**< Left direction (West) */
    DOWN   /**< Downwards direction (South) */
};

/**
 * @enum EntityType
 * @brief Represent the type of an Entity
 */
enum EntityType
{
    SPEARMAN,  /**< Spearman Object */
    GREEN_BLOB /**< Green Blob Object */
};

/**
 * @struct Entity
 * @brief Represents an Entity present in the game board
 */
struct Entity
{
    enum EntityType type; /**< Entity type */
    void *entity_info;    /**< Pointer to the especific entity object */
};

/**
 * @brief Moves an entity from position ( @p curr_x , @p curr_y ) to postition ( @p new_x, @p new_y )
 *
 * @param curr_x Entity's current X postition
 * @param curr_y Entity's current Y postition
 * @param new_x Entity's new X postition
 * @param new_y Entity's new Y postition
 * @return int 2 if the new postition is already occupied, 1 if the new postition is out of the board and 0 otherwise
 */
int grid_move(const uint8_t curr_x, const uint8_t curr_y, const uint8_t new_x, const uint8_t new_y);

/**
 * @brief Add @p entity to the game board
 *
 * @param entity Entity to add
 * @return int 1 if that postition is aready occupied, 0 otherwise
 */
int grid_add(struct Entity *entity);

/**
 * @brief Modifies the HP of an Entity in position ( @p x , @p y ) by @p health_mod
 *
 * @param x Entity's X postition
 * @param y Entity's Y postition
 * @param health_mod health modification
 * @return int 1 if the health mod is not possible, 0 otherwise
 */
int grid_health_mod(const uint8_t x, const uint8_t y, const char health_mod);

/**
 * @brief Updates the animations of all Entities
 *
 * @param frame current frame
 * @return int 1 death animation has finished, 0 otherwise
 */
int update_animations(const uint32_t frame);

/**
 * @brief Deletes the grid entities (frees memory)
 */
void delete_grid();

#endif
