#include "rect.h"

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
