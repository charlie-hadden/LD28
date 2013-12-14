#include "rect.h"

static bool rect_lines_cross(float x0, float y0, float x1, float y1,
		float x2, float y2, float x3, float y3);

rect_t*
rect_create(float x, float y, int w, int h) {
	rect_t *rect = (rect_t*)malloc(sizeof(rect_t));

	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;

	return rect;
}

void
rect_free(rect_t *rect) {
	free(rect);
}

bool
rect_intersecting(rect_t *a, rect_t *b) {
	return !(a->x - a->w / 2 > b->x + b->w / 2
			|| a->x + a->w / 2 < b->x - b->w / 2
			|| a->y - a->h / 2 > b->y + b->h / 2
			|| a->y + a->h / 2 < b->y - b->w / 2);
}

bool
rect_contains_point(rect_t *rect, float x, float y) {
	return (x < rect->x + rect->w / 2
			&& x > rect->x - rect->w / 2
			&& y < rect->y + rect->h / 2
			&& y > rect->y - rect->h / 2);
}

bool
rect_line_intersecs(rect_t *rect, float x0, float y0, float x1, float y1) {
	return false;
}

static bool
rect_lines_cross(float x0, float y0, float x1, float y1, float x2, float y2,
		float x3, float y3) {
	return false;
}
