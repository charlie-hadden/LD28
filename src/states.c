#include "states.h"

static state_t states_[NUM_STATES];
static states next_state_;
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

	// Game Over State
	states_[2].init = &gameover_init;
	states_[2].cleanup = &gameover_cleanup;
	states_[2].handle_event = &gameover_handle_event;
	states_[2].update = &gameover_update;
	states_[2].draw = &gameover_draw;

	states_set_state(0);
	next_state_ = STATE_NONE;
}

void
states_cleanup(void) {
	if (current_state_ && current_state_->cleanup)
		current_state_->cleanup();
}

void
states_update(void) {
	if (next_state_ != STATE_NONE) {
		states_set_state(next_state_);
		next_state_ = STATE_NONE;
	}
}

void
states_set_state(states state) {
	if (current_state_ && current_state_->cleanup)
		current_state_->cleanup();

	current_state_ = &states_[state];

	if (current_state_->init)
		current_state_->init();
}

void
states_queue_change(states state) {
	next_state_ = state;
}

state_t*
states_get_state(void) {
	return current_state_;
}
