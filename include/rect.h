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

#endif // RECT_H
