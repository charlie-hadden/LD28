#ifndef WINDOW_H
#define WINDOW_H

#include "common.h"
#include "rect.h"

void window_init(const char *title, int width, int height);
void window_cleanup(void);

void window_swap(void);
rect_t *window_get_rect(void);

#endif // WINDOW_H
