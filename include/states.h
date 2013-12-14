#ifndef STATES_H
#define STATES_H

#include "common.h"
#include "menu.h"
#include "game.h"
#include "gameover.h"

typedef struct {
	void (*init)(void);
	void (*cleanup)(void);
	void (*handle_event)(SDL_Event *event);
	void (*update)(unsigned int delta_time);
	void (*draw)(void);
} state_t;

#define NUM_STATES 3
typedef enum {
	STATE_NONE = -1,
	STATE_MENU = 0,
	STATE_GAME = 1,
	STATE_GAMEOVER = 2
} states;

void states_init(void);
void states_cleanup(void);

void states_update(void);

void states_set_state(states state);
void states_queue_change(states state);
state_t *states_get_state(void);

#endif // STATES_H
