#ifndef GAME_H
#define GAME_H

#include "common.h"
#include "player.h"
#include "bullet.h"

void game_init(void);
void game_cleanup(void);

void game_handle_event(SDL_Event *event);
void game_update(unsigned int delta_time);
void game_draw(void);

#endif // GAME_H
