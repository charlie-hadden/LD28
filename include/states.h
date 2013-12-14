#ifndef STATES_H
#define STATES_H

#include "common.h"
#include "game.h"

typedef struct {
	void (*init)(void);
	void (*cleanup)(void);
	void (*handle_event)(SDL_Event *event);
	void (*update)(unsigned int delta_time);
	void (*draw)(void);
} state_t;

#define NUM_STATES 1
typedef enum {
	STATE_GAME = 0
} states;

void states_init(void);
void states_cleanup(void);

void states_set_state(states state);
state_t *states_get_state(void);

#endif // STATES_H
