#ifndef BULLET_H
#define BULLET_H

#include "common.h"
#include "vector.h"

typedef enum {
	BULLET_ROUND
} bullet_type;

typedef struct {
	float x_pos, y_pos;
	float x_vel, y_vel;
	bullet_type type;
	float scale_x, scale_y;
} bullet_t;

void bullet_init(void);
void bullet_cleanup(void);

bullet_t *bullet_create(void);
void bullet_free(bullet_t *bullet);

void bullet_spawn(bullet_t *bullet);
void bullet_draw(void);

#endif // BULLET_H
