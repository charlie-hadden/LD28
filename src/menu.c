#include "menu.h"

#define NUM_MENU_BUTTONS 1
static menu_button_t buttons_[NUM_MENU_BUTTONS];

static void menu_click_play(void);

void
menu_init(void) {
	buttons_[0].text = text_write("PLAY", &buttons_[0].w, &buttons_[0].h);
	buttons_[0].rect = rect_create(window_width() / 2, window_height() - 75, 200, 50);
	buttons_[0].click = &menu_click_play;
}

void
menu_cleanup(void) {
	for (unsigned i = 0; i < NUM_MENU_BUTTONS; i++) {
		glDeleteTextures(1, &buttons_[i].text);
		rect_free(buttons_[i].rect);
	}
}

void
menu_handle_event(SDL_Event *event) {
	if (event->type == SDL_MOUSEBUTTONDOWN
			&& event->button.button == SDL_BUTTON_LEFT) {
		for (int i = 0; i < NUM_MENU_BUTTONS; i++) {
			if (rect_contains_point(buttons_[i].rect, event->button.x,
						event->button.y)
					&& buttons_[i].click) {
				buttons_[i].click();
			}
		}
	}
}

void
menu_update(unsigned int delta_time) {
}

void
menu_draw(void) {
	int mouse_x, mouse_y;
	SDL_GetMouseState(&mouse_x, &mouse_y);

	// Draw backgrounds
	SDL_Color color;
	glBegin(GL_QUADS);
	for (int i = 0; i < NUM_MENU_BUTTONS; i++) {
		float x = buttons_[i].rect->x, y = buttons_[i].rect->y;
		float half_w = buttons_[i].rect->w / 2, half_h = buttons_[i].rect->h / 2;

		if (rect_contains_point(buttons_[i].rect, mouse_x, mouse_y)) {
			color = color_get(COLOR_ENEMY + 15);
		} else {
			color = color_get(COLOR_ENEMY);
		}
		glColor3f(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f);

		glVertex2f(x - half_w, y - half_h);
		glVertex2f(x + half_w, y - half_h);
		glVertex2f(x + half_w, y + half_h);
		glVertex2f(x - half_w, y + half_h);
	}
	glEnd();

	// Draw lables
	color = color_get(COLOR_PLAYER);
	glColor3i(color.r, color.g, color.b);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	for (int i = 0; i < NUM_MENU_BUTTONS; i++) {
		float x = buttons_[i].rect->x, y = buttons_[i].rect->y;
		int w = buttons_[i].w, h = buttons_[i].h;

		glBindTexture(GL_TEXTURE_2D, buttons_[i].text);
		glColor3f(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f);

		glTexCoord2f(0.0, 0.0);
		glVertex2f(x - w / 2, y - h / 2);

		glTexCoord2f(1.0, 0.0);
		glVertex2f(x + w / 2, y - h / 2);

		glTexCoord2f(1.0, 1.0);
		glVertex2f(x + w / 2, y + h / 2);

		glTexCoord2f(0.0, 1.0);
		glVertex2f(x - w / 2, y + h / 2);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

static void
menu_click_play(void) {
	states_queue_change(STATE_GAME);
}
