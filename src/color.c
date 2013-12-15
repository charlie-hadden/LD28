#include "color.h"

static float hue_ = 0;

static float color_to_rgb(float p, float q, float t);

void
color_init(void) {
	hue_ = rand() % 360;
}

void
color_update() {
	hue_ += 0.1;

	if (hue_ >= 360)
		hue_ -= 360;
}

SDL_Color
color_get(colors color) {
	float s = 1.0f;
	float l = 0.5f;

	float q = (l < 0.5) ? l * (1 + s) : l + s - l * s;
	float p = 2.0f * l - q;

	float hue = hue_ + color;
	while (hue > 360)
		hue -= 360;
	while (hue < 0)
		hue += 360;
	hue = hue / 360.0f;

	float r = color_to_rgb(p, q, hue + 1.0f / 3.0f);
	float g = color_to_rgb(p, q, hue);
	float b = color_to_rgb(p, q, hue - 1.0f / 3.0f);

	SDL_Color sdl_color = { r * 255, g * 255, b * 255 };

	return sdl_color;
}

static float
color_to_rgb(float p, float q, float t) {
	if (t < 0)
		t += 1;

	if (t > 1)
		t -= 1;

	if (t < 1.0f / 6.0f)
		return p + (q - p) * 6.0f * t;

	if (t < 1.0f / 2.0f)
		return q;

	if (t < 2.0f / 3.0f)
		return p + (q - p) * (2.0f / 3.0f - t) * 6.0f;

	return p;
}
