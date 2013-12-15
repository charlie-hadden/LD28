#include "game.h"

static float difficulty_ = 1.0;
static bool game_over_ = false;

void
game_init(void) {
	game_over_ = false;
	enemy_init();
	bullet_init();
	player_init();
	window_set_grab(true);
	SDL_ShowCursor(false);
}

void
game_cleanup(void) {
	enemy_cleanup();
	bullet_cleanup();
	player_cleanup();
	window_set_grab(false);
	SDL_ShowCursor(true);
}

void
game_handle_event(SDL_Event *event) {
}

void
game_update(void) {
	const uint8_t *keys = SDL_GetKeyboardState(NULL);
	if (game_over_ && keys[SDL_SCANCODE_SPACE])
		states_queue_change(STATE_MENU);

	if (!game_over_) {
		color_update();
		enemy_update();
		player_update();
		bullet_update();
	}
}

void
game_draw(void) {
	bullet_draw();
	enemy_draw();
	player_draw();
}

float
game_get_difficulty(void) {
	return difficulty_;
}

void
game_set_difficulty(float difficulty) {
	difficulty_ = difficulty;
}

void
game_gameover(void) {
	game_over_ = true;
}
