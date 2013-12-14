#include "game.h"

void
game_init(void) {
	bullet_init();
	player_init();
}

void
game_cleanup(void) {
	bullet_cleanup();
	player_cleanup();
}

void
game_handle_event(SDL_Event *event) {
}

static float angle = 0;
static int fire_interval = 100, fire_cooldown = 0;

void
game_update(unsigned int delta_time) {
	fire_cooldown -= delta_time;
	if (fire_cooldown <= 0) {
		bullet_t *bullet = bullet_create();
		bullet->rect = rect_create(300, 100, 10, 10);
		bullet->x_vel = sin(angle) * 0.2;
		bullet->y_vel = cos(angle) * 0.5;
		bullet->type = BULLET_SQUARE;
		bullet_spawn(bullet);

		bullet = bullet_create();
		bullet->rect = rect_create(300, 100, 10, 10);
		bullet->x_vel = -sin(angle) * 0.2;
		bullet->y_vel = -cos(angle) * 0.5;
		bullet->type = BULLET_SQUARE;
		bullet_spawn(bullet);

		fire_cooldown = fire_interval;
		angle += 0.2;
	}

	player_update(delta_time);
	bullet_update(delta_time);
}

void
game_draw(void) {
	bullet_draw();
	player_draw();
}
