#ifndef WINDOW_H
#define WINDOW_H

#include "common.h"

void window_init(const char *title, int width, int height);
void window_cleanup(void);

void window_swap(void);
SDL_Renderer *window_get_renderer(void);

#endif // WINDOW_H
