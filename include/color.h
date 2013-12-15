#ifndef COLOR_H
#define COLOR_H

#include "common.h"

typedef enum {
	COLOR_BASE = 0,
	COLOR_ENEMY = 360 / 3,
	COLOR_PLAYER = (360 / 3) * 2
} colors;

void color_init(void);
void color_update(void);

SDL_Color color_get(colors color);

#endif // COLOR_H
