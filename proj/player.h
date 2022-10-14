#ifndef PLAYER_H_
#define PLAYER_H_
#include <lcom/lcf.h>
#include "entities.h"

struct GridImage; //forward declaration

/**
 * @enum SpearmanAction
 * @brief Enumerator that represents the spearman's current action
 */
enum SpearmanAction
{
    SPEARMAN_MOVE_RIGHT,    /**<@brief Moving right */
    SPEARMAN_MOVE_UP,       /**<@brief Moving up */
    SPEARMAN_MOVE_LEFT,     /**<@brief Moving left */
    SPEARMAN_MOVE_DOWN,     /**<@brief Moving down */
    SPEARMAN_ATTACK,        /**<@brief Attacking */
    SPEARMAN_SPECIAL_RIGHT, /**<@brief Special ability to the right */
    SPEARMAN_SPECIAL_UP,    /**<@brief Special ability upwards */
    SPEARMAN_SPECIAL_LEFT,  /**<@brief Special ability to the left */
    SPEARMAN_SPECIAL_DOWN,  /**<@brief Special ability downwards */
    SPEARMAN_DEAD,          /**<@brief Dead */
    SPEARMAN_NO_ACT         /**<@brief Idle */
};

/**
 * @struct SpearMan
 * @brief SpearMan object (main character)
 */
struct SpearMan
{
    char HP;                          /**<@brief Spearman's current health */
    char maxHP;                       /**<@brief Spearman's health pool */
    uint8_t dmg;                      /**<@brief Spearman's base damage */
    bool special_in_cd;               /**<@brief Spearman's special on cooldown */
    uint8_t special_cd;               /**<@brief Spearman's special cooldown */
    uint8_t special_range;            /**<@brief Spearman's special range */
    uint8_t special_dmg;              /**<@brief Spearman's special damage */
    bool channeling_special;          /**<@brief Spearman's channeling special */
    uint8_t x;                        /**<@brief Spearman's current X position */
    uint8_t y;                        /**<@brief Spearman's current Y position */
    enum SpearmanAction curr_action;  /**<@brief Spearman's current action */
    struct GridImage *current_sprite; /**<@brief Spearman's current sprite to be drawn */
    enum Direction d;                 /**<@brief Spearman's direction */
    uint8_t target_x;                 /**<@brief Spearman's special target */
    uint8_t target_y;                 /**<@brief Spearman's special target */
};

struct Entity *create_spearman(const uint8_t x, const uint8_t y);

/**
 * @brief The spearman acts acording to action in @p PA
 *
 * @param spearman spearman that will act
 * @param PA Action
 * @return int 2 if the spearman is dead, 1 if the spearman action is not permited 0 otherwise
 */
int spearman_act(struct SpearMan *spearman, enum SpearmanAction PA);

/**
 * @brief The spearman attacks in its direction
 *
 * @param spearman spearman that will attack
 * @return int 1 if the attack fails, 0 otherwise
 */
int spearman_attack(struct SpearMan *spearman);

/**
 * @brief The spearman moves in @p direction
 *
 * @param spearman spearman that will move
 * @param direction direction that this spearman will move
 * @return int 1 if he can not move, 0 otherwise
 */
int spearman_move(struct SpearMan *spearman, const enum Direction direction);

/**
 * @brief The spearman uses its special ability
 *
 * @param spearman spearman that will use the special
 * @return int 1 if the special ability fails, 0 otherwise
 */
int spearman_special(struct SpearMan *spearman);

/**
 * @brief Animates the spearman according to its action
 *
 * @param spearman spearman to animate
 * @param frame current frame
 * @return int 1 if the spearman death animation has ended, 0 otherwise
 */
int animate_spearman(struct SpearMan *spearman, const uint32_t frame);

/**
 * @brief Animates the spearman's special attack
 *
 * @param spearman spearman to animate
 * @param frame current frame
 */
void animate_spearman_special(struct SpearMan *spearman, const uint32_t frame);

/**
 * @brief Animates the spearman's attack
 *
 * @param spearman spearman to animate
 * @param frame current frame
 */
void animate_spearman_attack(struct SpearMan *spearman, const uint32_t frame);

/**
 * @brief Animates the spearman's directional move
 *
 * @param spearman spearman to animate
 * @param frame current frame
 */
void animate_spearman_move(struct SpearMan *spearman, const uint32_t frame);

/**
 * @brief Animates the spearman's directional move
 *
 * @param spearman spearman to animate
 * @param frame current frame
 * @return 1 if the death animation has finished, 0 otherwise
 */
int animate_spearman_death(struct SpearMan *spearman, const uint32_t frame);

#endif
