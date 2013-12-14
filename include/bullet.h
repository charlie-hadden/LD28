#ifndef BULLET_H
#define BULLET_H

#include "common.h"
#include "vector.h"
#include "rect.h"
#include "player.h"

typedef enum {
	BULLET_ROUND,
	BULLET_SQUARE
} bullet_type;

typedef struct {
	rect_t *rect;
	float x_vel, y_vel;
	bullet_type type;
} bullet_t;

void bullet_init(void);
void bullet_cleanup(void);

bullet_t *bullet_create(void);
void bullet_free(bullet_t *bullet);

void bullet_spawn(bullet_t *bullet);
void bullet_update(unsigned int delta_time);
void bullet_draw(void);

#endif // BULLET_H
