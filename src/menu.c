#include "menu.h"

#define NUM_MENU_BUTTONS 4
static menu_button_t buttons_[NUM_MENU_BUTTONS];

static GLuint super_, pewpew_;
static int super_h_, super_w_, pewpew_h_, pewpew_w_;

static void menu_click_easy(void);
static void menu_click_normal(void);
static void menu_click_hard(void);
static void menu_click_nope(void);

void
menu_init(void) {
	super_ = text_write_big("SUPER", &super_w_, &super_h_);
	pewpew_ = text_write_big("PEW-PEW", &pewpew_w_, &pewpew_h_);

	buttons_[0].text = text_write("EASY", &buttons_[0].w, &buttons_[0].h);
	buttons_[0].rect = rect_create(window_width() / 2, 375, 300, 50);
	buttons_[0].click = &menu_click_easy;

	buttons_[1].text = text_write("NORMAL", &buttons_[1].w, &buttons_[1].h);
	buttons_[1].rect = rect_create(window_width() / 2, 475, 300, 50);
	buttons_[1].click = &menu_click_normal;

	buttons_[2].text = text_write("HARD", &buttons_[2].w, &buttons_[2].h);
	buttons_[2].rect = rect_create(window_width() / 2, 575, 300, 50);
	buttons_[2].click = &menu_click_hard;

	buttons_[3].text = text_write("NOPE", &buttons_[3].w, &buttons_[3].h);
	buttons_[3].rect = rect_create(window_width() / 2, 675, 300, 50);
	buttons_[3].click = &menu_click_nope;

}

void
menu_cleanup(void) {
	glDeleteTextures(1, &super_);
	glDeleteTextures(1, &pewpew_);

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

	// Draw header
	SDL_Color bc = color_get(COLOR_BASE);

	if (bc.r * 0.299 + bc.g * 0.587 + bc.b * 0.114 > 186) {
		glColor3f(0, 0, 0);
	} else {
		glColor3f(1, 1, 1);
	}

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, super_);
	glBegin(GL_QUADS);

	float off_x = 300, off_y = 130;

	glTexCoord2f(0, 0);
	glVertex2f(off_x - super_w_ / 2, off_y - super_h_ / 2);
	glTexCoord2f(1, 0);
	glVertex2f(off_x + super_w_ / 2, off_y - super_h_ / 2);
	glTexCoord2f(1, 1);
	glVertex2f(off_x + super_w_ / 2, off_y + super_h_ / 2);
	glTexCoord2f(0, 1);
	glVertex2f(off_x - super_w_ / 2, off_y + super_h_ / 2);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, pewpew_);
	glBegin(GL_QUADS);

	off_x = 300, off_y = 230;

	glTexCoord2f(0, 0);
	glVertex2f(off_x - pewpew_w_ / 2, off_y - pewpew_h_ / 2);
	glTexCoord2f(1, 0);
	glVertex2f(off_x + pewpew_w_ / 2, off_y - pewpew_h_ / 2);
	glTexCoord2f(1, 1);
	glVertex2f(off_x + pewpew_w_ / 2, off_y + pewpew_h_ / 2);
	glTexCoord2f(0, 1);
	glVertex2f(off_x - pewpew_w_ / 2, off_y + pewpew_h_ / 2);

	glEnd();

	glDisable(GL_TEXTURE_2D);

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
	glColor3f(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f);
	glEnable(GL_TEXTURE_2D);
	for (int i = 0; i < NUM_MENU_BUTTONS; i++) {
		float x = buttons_[i].rect->x, y = buttons_[i].rect->y;
		int w = buttons_[i].w, h = buttons_[i].h;

		glBindTexture(GL_TEXTURE_2D, buttons_[i].text);
		glBegin(GL_QUADS);

		glTexCoord2f(0.0, 0.0);
		glVertex2f(x - w / 2, y - h / 2);

		glTexCoord2f(1.0, 0.0);
		glVertex2f(x + w / 2, y - h / 2);

		glTexCoord2f(1.0, 1.0);
		glVertex2f(x + w / 2, y + h / 2);

		glTexCoord2f(0.0, 1.0);
		glVertex2f(x - w / 2, y + h / 2);
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
}

static void
menu_click_easy(void) {
	game_set_difficulty(0.4f);
	states_queue_change(STATE_GAME);
}

static void
menu_click_normal(void) {
	game_set_difficulty(1.0f);
	states_queue_change(STATE_GAME);
}

static void
menu_click_hard(void) {
	game_set_difficulty(2.0f);
	states_queue_change(STATE_GAME);
}

static void
menu_click_nope(void) {
	game_set_difficulty(3.0f);
	states_queue_change(STATE_GAME);
}
