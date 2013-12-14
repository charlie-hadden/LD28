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

void
game_update(unsigned int delta_time) {
	player_update(delta_time);
	bullet_update(delta_time);
}

void
game_draw(void) {
	bullet_draw();
	player_draw();
}
