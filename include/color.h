#ifndef COLOR_H
#define COLOR_H

#include "common.h"

typedef enum {
	COLOR_BACKGROUND,
	COLOR_FRIENDLY_A,
	COLOR_FRIENDLY_B,
	COLOR_HOSTILE_A,
	COLOR_HOSTILE_B
} colors;

void color_init(void);
void color_update(unsigned int delta_time);

SDL_Color color_get(colors color);

#endif // COLOR_H
