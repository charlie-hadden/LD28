#include "states.h"

static state_t states_[NUM_STATES];
static state_t *current_state_;

void
states_init(void) {
	// Menu State
	states_[0].init = &menu_init;
	states_[0].cleanup = &menu_cleanup;
	states_[0].handle_event = &menu_handle_event;
	states_[0].update = &menu_update;
	states_[0].draw = &menu_draw;

	// Game State
	states_[1].init = &game_init;
	states_[1].cleanup = &game_cleanup;
	states_[1].handle_event = &game_handle_event;
	states_[1].update = &game_update;
	states_[1].draw = &game_draw;

	states_set_state(0);
}

void
states_cleanup(void) {
	if (current_state_ && current_state_->cleanup)
		current_state_->cleanup();
}

void
states_set_state(states state) {
	if (current_state_ && current_state_->cleanup)
		current_state_->cleanup();

	current_state_ = &states_[state];

	if (current_state_->init)
		current_state_->init();
}

state_t*
states_get_state(void) {
	return current_state_;
}
