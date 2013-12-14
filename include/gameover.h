#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "common.h"
#include "states.h"

void gameover_init(void);
void gameover_cleanup(void);

void gameover_handle_event(SDL_Event *event);
void gameover_update(unsigned int delta_time);
void gameover_draw();

#endif // GAMEOVER_H
