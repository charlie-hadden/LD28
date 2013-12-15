#include "game.h"

static bool game_over_ = false;

void
game_init(void) {
	game_over_ = false;
	bullet_init();
	player_init();
	window_set_grab(true);
	SDL_ShowCursor(false);
}

void
game_cleanup(void) {
	bullet_cleanup();
	player_cleanup();
	window_set_grab(false);
	SDL_ShowCursor(true);
}

void
game_handle_event(SDL_Event *event) {
}

static float angle = 0;
static int fire_interval = 30, fire_cooldown = 0;

void
game_update(void) {
	fire_cooldown--;
	if (fire_cooldown <= 0) {
		bullet_t *bullet = bullet_create();
		bullet->rect = rect_create(300, 100, 20, 20);
		bullet->x_vel = sin(angle) * 1.2;
		bullet->y_vel = cos(angle) * 1.5;
		bullet->type = BULLET_SQUARE;
		bullet->player = false;
		bullet_spawn(bullet);

		bullet = bullet_create();
		bullet->rect = rect_create(300, 100, 20, 20);
		bullet->x_vel = -sin(angle) * 1.2;
		bullet->y_vel = -cos(angle) * 1.5;
		bullet->type = BULLET_SQUARE;
		bullet->player = false;
		bullet_spawn(bullet);

		fire_cooldown = fire_interval;
		angle -= 0.2;
	}

	const uint8_t *keys = SDL_GetKeyboardState(NULL);
	if (game_over_ && keys[SDL_SCANCODE_SPACE])
		states_queue_change(STATE_MENU);

	if (!game_over_) {
		color_update();
		player_update();
		bullet_update();
	}
}

void
game_draw(void) {
	bullet_draw();
	player_draw();
}

void
game_gameover(void) {
	game_over_ = true;
}
