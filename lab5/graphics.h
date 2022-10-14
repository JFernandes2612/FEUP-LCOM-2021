#ifndef GRAPHICS_H
#define GRAPHICS_H

void video_refresh();

void paint_pixel(uint16_t x, uint16_t y, uint32_t colour);

int paint_xpm(xpm_image_t *img, uint16_t start_x, uint16_t start_y);

int file_to_xpm(const char* filepath, xpm_image_t *img);

#endif
