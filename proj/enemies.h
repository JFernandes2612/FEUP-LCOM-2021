#ifndef ENEMIES_H
#define ENEMIES_H

#include <lcom/lcf.h>
#include "entities.h"

/**
 * @enum GreenBlobAction
 * @brief Enumerator that represents the state of a blob
 */
enum GreenBlobAction
{
    GREEN_BLOB_MOVE_RIGHT, /**< Moving right */
    GREEN_BLOB_MOVE_UP,    /**< Moving upwards */
    GREEN_BLOB_MOVE_LEFT,  /**< Moving left */
    GREEN_BLOB_MOVE_DOWN,  /**< Moving downwards */
    GREEN_BLOB_ATTACK,     /**< Attacking */
    GREEN_BLOB_NO_ACT,     /**< Idle */
    GREEN_BLOB_DEAD        /**< Dead */
};

/**
 * @struct GreenBlob
 * @brief Enemy green blob (green slime) structure
 */
struct GreenBlob
{
    char HP;                          /**< Health of the Green Blob */
    char dmg;                         /**< Damage per atack */
    uint8_t x;                        /**< X grid position */
    uint8_t y;                        /**< Y grid position */
    enum Direction direction;         /**< Current Green Blob orientation */
    enum GreenBlobAction action;      /**< Current state of the green blob */
    struct GridImage *current_sprite; /**< Current sprite that will be used in the drawing of the grid */
};

/**
 * @brief Create a green blob object (entity)
 *
 * @param x X position on the grid
 * @param y Y position on the grid
 * @param movement Inicial orientation of the blob
 * @return struct Entity*
 */
struct Entity *create_g_blob(uint8_t x, uint8_t y, enum Direction movement);

/**
 * @brief Makes the blob act (move or attack)
 *
 * @param green_blob green blob that will act
 * @return int 0 if it does not fail, 1 if it fails, 2 if the blob is dead and no action is possible
 *
 * @note The blobs always move in clockwise motion, if the blob can not move in the desired direction it will attack
 */
int green_blob_act(struct GreenBlob *green_blob);

/**
 * @brief Moves every enemy in the grid
 *
 * @return int 1 if no enemies are moved, 0 otherwise
 */
int grid_enemies_move();

/**
 * @brief Animates the green blobs depending on their current action
 *
 * @param gb  green blob to animate
 * @param frame current frame
 */
void animate_green_blob(struct GreenBlob *gb, const uint32_t frame);

/**
 * @brief Animates the green blobs idle state
 *
 * @param gb  green blob to animate
 * @param frame current frame
 */
void animate_green_blob_idle(struct GreenBlob *gb, const uint32_t frame);

/**
 * @brief Animates the green blobs moving state
 *
 * @param gb  green blob to animate
 * @param frame current frame
 */
void animate_green_blob_move(struct GreenBlob *gb, const uint32_t frame);

/**
 * @brief Animates the green blobs dying
 *
 * @param gb  green blob to animate
 * @param frame current frame
 */
void animate_green_blob_death(struct GreenBlob *gb, const uint32_t frame);

/**
 * @brief Animates the green blobs attacking
 *
 * @param gb  green blob to animate
 * @param frame current frame
 */
void animate_green_blob_attack(struct GreenBlob *gb, const uint32_t frame);

#endif
