#ifndef MENU_H
#define MENU_H

#include "common.h"
#include "rect.h"

typedef struct {
	const char *text;
	rect_t *rect;
} menu_button_t;

void menu_init(void);
void menu_cleanup(void);

void menu_handle_event(SDL_Event *event);
void menu_update(unsigned int delta_time);
void menu_draw(void);

#endif // MENU_H
