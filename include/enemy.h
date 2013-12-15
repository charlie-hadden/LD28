#ifndef ENEMY_H
#define ENEMY_H

#include "common.h"
#include "game.h"
#include "rect.h"

typedef enum {
	ENEMY_STRAFER
} enemy_type;

typedef struct {
	rect_t *rect;
	float last_x_vel, last_y_vel;
	enemy_type type;
	float angle;
	int cooldown, fire_rate;
} enemy_t;

#define MAX_ENEMIES 50

void enemy_init(void);
void enemy_cleanup(void);

enemy_t *enemy_create(void);
void enemy_free(enemy_t *enemy);

void enemy_spawn(enemy_t *enemy);
void enemy_update(void);
void enemy_draw(void);

#endif // ENEMY_H
