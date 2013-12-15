#ifndef RECT_H
#define RECT_H

#include "common.h"

typedef struct {
	float x, y;
	int w, h;
} rect_t;

rect_t *rect_create(float x, float y, int w, int h);
void rect_free(rect_t *rect);

bool rect_intersecting(rect_t *a, rect_t *b);
bool rect_contains_point(rect_t *rect, float x, float y);
bool rect_line_intersects(rect_t *rect, float x0, float y0, float x1, float y1);
bool rect_collides(rect_t *a, rect_t *b, vec3 vel);

#endif // RECT_H
