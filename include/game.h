#ifndef GAME_H
#define GAME_H

#include "common.h"
#include "player.h"
#include "bullet.h"
#include "states.h"

void game_init(void);
void game_cleanup(void);

void game_handle_event(SDL_Event *event);
void game_update(void);
void game_draw(void);

void game_gameover(void);

#endif // GAME_H
