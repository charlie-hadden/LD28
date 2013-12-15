#ifndef ENEMY_H
#define ENEMY_H

#include "common.h"
#include "rect.h"

typedef struct {
	rect_t *rect;
	float last_x_vel, last_y_vel;
	float angle;
} enemy_t;

#define MAX_ENEMIES 50

void enemy_init(void);
void enemy_cleanup(void);

enemy_t *enemy_create(void);
void enemy_free(enemy_t *enemy);

void enemy_spawn(enemy_t *enemy);
void enemy_update(unsigned int delta_time);
void enemy_draw(void);

#endif // ENEMY_H
