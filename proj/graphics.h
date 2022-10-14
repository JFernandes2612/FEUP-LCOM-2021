#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "player.h"
#include "enemies.h"

/**
 * @brief Game cursor
 */
struct Cursor
{
    /**
     * @brief Screen cursor X position
     */
    int16_t x;
    /**
     * @brief Screen cursor Y position
     */
    int16_t y;
};

/**
 * @brief Create a cursor object
 *
 * @return struct Cursor*
 */
struct Cursor* create_cursor();

/**
 * @brief Updates the mouse position
 *
 * @param c cursor to make the changes on
 * @param delta_x change to the x value of the mouse
 * @param delta_y change to the y value of the mouse
 */
void update_mouse_position(struct Cursor* c, const int16_t delta_x, const int16_t delta_y);

/**
 * @brief Calculates the grid position of the cursor
 *
 * @param c Cursor from which to calculate the position
 * @param x_grid address to write the x position of the cursor in the grid
 * @param y_grid address to write the y position of the cursor in the grid
 * @return int 1 if the mouse is out of bounds, 0 otherwise
 */
int mouse_grid_pos(struct Cursor* c, uint8_t *x_grid, uint8_t *y_grid);

/**
 * @brief Paints the Cursor
 *
 * @param c cursor to be painted
 * @return int 1 if it fails, 0 otherwise
 */
int paint_cursor(struct Cursor* c);

/**
 * @brief Enable minix graphics mode in mode @p 0x14C
 *
 * @return int 1 if this process failed 0 otherwise
 */
int vg_init_ours();

/**
 * @brief Disable the graphics mode and frees the video mem alocated as well as the buffer
 *
 * @return int 1 if it fails 0 otherwise
 */
int vg_exit_ours();

/**
 * @brief Refreshes the screen
 */
void video_refresh();

/**
 * @brief Generates a new background (including UI background)
 * @note this function normaly does not fail since this printing is done in a controlled loop
 */
int create_background();

/**
 * @brief Paints the UI elements to the screen
 *
 * @param s spearman to paint UI
 *
 * @return int 1 if it fails, 0 otherwise
 */
int paint_UI(struct SpearMan *s);

/**
 * @brief Prints the lateral walls of the game board
 *
 * @return int 1 if it fails 0 otherwise
 *
 * @note this function normaly does not fail since this printing is done in a controlled loop
 */
int paint_background_lateral_walls();

/**
 * @brief Paints the entities of the game (playes, monsters, etc)
 * @return int 1 if it fails 0 otherwise
 */
int paint_grid();

/**
 * @brief Paints in the screen @p s
 *
 * @param s string to print
 * @param x Base X value
 * @param y Base Y value
 * @param background true if the text will be painted in the background layer, false otherwise
 * @return int 1 if it fails, 0 otherwise
 *
 * @note NOT ALL CHARACTERS ARE ACCEPTED - only uppercase and symbols like ',' '.' '!' '?' are
 */
int paint_text(const char* s, const uint16_t x, const uint16_t y, bool background);

/**
 * @brief Paints a pixel in coordinates ( @p x , @p y ) with @p colour
 *
 * @param x Horizontal coordinate
 * @param y Vertical coordinate
 * @param colour 32 bit colour
 * @param background true if the pixel will be painted in the background buffer false otherwise
 * @return int 1 if it is impossible to paint that pixel 0 otherwise
 */
int paint_pixel(const uint16_t x, const uint16_t y, const uint32_t colour, const bool background);

/**
 * @brief Paints a XPM file in the screen at coordinates ( @p start_x , @p start_y )
 *
 * @param img XPM struct that contains all the information regarding a xpm image
 * @param start_x Horizontal coordinate
 * @param start_y Vertical coordinate
 * @param background true if the pixel will be painted in the background buffer false otherwise
 * @return int 1 if it is not possible to paint the XPM in the space available
 */
int paint_xpm(const xpm_image_t *img, const uint16_t start_x, const uint16_t start_y, const bool background);

/**
 * @brief Fills an area of the screen
 *
 * @param start_x Horizontal coordinate
 * @param start_y Vertical coordinate
 * @param width Width to be painted (left)
 * @param height Heidht to be painted (downwards)
 * @param colour Colour to be painted
 * @param background true if the pixel will be painted in the background buffer false otherwise
 * @return int 1 it it can not fill that area, 0 otherwise
 */
int paint_area(const uint16_t start_x, const uint16_t start_y, const uint16_t width, const uint16_t height, const uint32_t colour, const bool background);

/**
 * @brief Generates a struct containing all the information regarding a XPM in @p img
 *
 * @param filepath .xpm file file path
 * @param img return value regarding this XPM file
 * @return int 1 if the file does not exist
 * @return int 2 the file read is not valid or has a invalid format
 * @return int 0 if it works
 */
int file_to_xpm(const char *filepath, xpm_image_t *img);

/**
 * @brief Refreshes the background to be displayed
 */
void background_refresh();

#endif
