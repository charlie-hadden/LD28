#ifndef WINDOW_H
#define WINDOW_H

#include "common.h"
#include "rect.h"

void window_init(const char *title, int width, int height);
void window_cleanup(void);

int window_width(void);
int window_height(void);

void window_swap(void);
rect_t *window_get_rect(void);
void window_set_grab(bool grab);
void window_warp_cursor(int x, int y);

#endif // WINDOW_H
