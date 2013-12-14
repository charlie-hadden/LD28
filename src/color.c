#include "color.h"

static SDL_Color background_ = { 0xFF, 0xFA, 0x00 };
static SDL_Color friendly_a_ = { 0x20, 0xDD, 0x20 };
static SDL_Color friendly_b_ = { 0x20, 0xFF, 0x20 };
static SDL_Color hostile_a_ = { 0xDD, 0x20, 0x20 };
static SDL_Color hostile_b_ = { 0xFF, 0x20, 0x20 };

void
color_init(void) {
}

void
color_update(unsigned int delta_time) {
	float r = delta_time;
	float g = delta_time;
	float b = delta_time;

	background_.r += 1;
	background_.g += 1;
	background_.b += 1;
}

SDL_Color
color_get(colors color) {
	switch(color) {
		case COLOR_BACKGROUND: return background_;
		case COLOR_FRIENDLY_A: return friendly_a_;
		case COLOR_FRIENDLY_B: return friendly_b_;
		case COLOR_HOSTILE_A: return hostile_a_;
		case COLOR_HOSTILE_B: return hostile_b_;
	}

	SDL_Color ret = { 0, 0, 0 };
	return ret;
}
