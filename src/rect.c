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
rect_line_intersects(rect_t *rect, float x0, float y0, float x1, float y1) {
	float x = rect->x, y = rect->y, w = rect->w / 2, h = rect->h / 2;

	bool top = rect_lines_cross(x - w, y - h, x + w, y - h, x0, y0, x1, y1);
	bool right = rect_lines_cross(x + w, y - h, x + w, y + h, x0, y0, x1, y1);
	bool bott = rect_lines_cross(x + w, y + h, x - w, y + h, x0, y0, x1, y1);
	bool left = rect_lines_cross(x - w, y + h, x - w, y - h, x0, y0, x1, y1);

	return top || right || bott || left;
}

bool
rect_collides(rect_t *a, rect_t *b, vec3 vel) {
	// Rect a is static for this check, rect b moves by vel.
	float w = b->w / 2, h = b->h / 2;
	float x0 = b->x, y0 = b->y;
	float x1 = b->x + vel[0], y1 = b->y + vel[1];

	bool tl = rect_line_intersects(a, x0 - w, y0 - h, x1 - w, y1 - h);
	bool tr = rect_line_intersects(a, x0 + w, y0 - h, x1 + w, y1 - h);
	bool br = rect_line_intersects(a, x0 + w, y0 + h, x1 + w, y1 + h);
	bool bl = rect_line_intersects(a, x0 - w, y0 + h, x1 - w, y1 + h);

	return tl || tr || br || bl;
}

static bool
rect_lines_cross(float x0, float y0, float x1, float y1, float x2, float y2,
		float x3, float y3) {
	float ua_t = (x3 - x2) * (y0 - y2) - (y3 - y2) * (x0 - x2);
	float ub_t = (x1 - x0) * (y0 - y2) - (y1 - y0) * (x0 - x2);
	float u_b = (y3 - y2) * (x1 - x0) - (x3 - x2) * (y1 - y0);

	if (u_b) {
		float ua = ua_t / u_b;
		float ub = ub_t / u_b;

		return 0 <= ua && ua <= 1 && 0 <= ub && ub <= 1;
	}

	return 0;
}
