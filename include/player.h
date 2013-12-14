#ifndef PLAYER_H
#define PLAYER_H

#include "common.h"
#include "rect.h"

void player_init(void);
void player_cleanup(void);

void player_update(unsigned int delta_time);
void player_draw(void);

rect_t *player_get_rect(void);

#endif // PLAYER_H
