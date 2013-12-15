#ifndef PLAYER_H
#define PLAYER_H

#include "common.h"
#include "rect.h"
#include "bullet.h"

void player_init(void);
void player_cleanup(void);

void player_update(void);
void player_draw(void);

rect_t *player_get_rect(void);

#endif // PLAYER_H
