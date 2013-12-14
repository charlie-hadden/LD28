#include "menu.h"

#define NUM_MENU_BUTTONS 1
static menu_button_t buttons_[NUM_MENU_BUTTONS];

void
menu_init(void) {
	buttons_[0].rect = rect_create(140, 40, 200, 50);
}

void
menu_cleanup(void) {
}

void
menu_handle_event(SDL_Event *event) {
}

void
menu_update(unsigned int delta_time) {
}

void
menu_draw(void) {
	int mouse_x, mouse_y;
	SDL_GetMouseState(&mouse_x, &mouse_y);

	glBegin(GL_QUADS);

	for (int i = 0; i < NUM_MENU_BUTTONS; i++) {
		float x = buttons_[i].rect->x, y = buttons_[i].rect->y;
		float half_w = buttons_[i].rect->w / 2, half_h = buttons_[i].rect->h / 2;

		if (rect_contains_point(buttons_[i].rect, mouse_x, mouse_y)) {
			glColor3f(0.0, 0.0, 0.0);
		} else {
			glColor3f(1.0, 1.0, 1.0);
		}

		glVertex2f(x - half_w, y - half_h);
		glVertex2f(x + half_w, y - half_h);
		glVertex2f(x + half_w, y + half_h);
		glVertex2f(x - half_w, y + half_h);
	}

	glEnd();
}
