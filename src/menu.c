#include "menu.h"

static TTF_Font *font_;

#define NUM_MENU_BUTTONS 1
static menu_button_t buttons_[NUM_MENU_BUTTONS];

static GLuint menu_draw_text(const char *text, int *w, int *h);

static void menu_click_play(void);

void
menu_init(void) {
	if (TTF_Init() == -1)
		fprintf(stderr, "Could not initialize SDL_ttf: %s\n", TTF_GetError());

	font_ = TTF_OpenFont("assets/ABSTRACT.TTF", 18);
	if (!font_)
		fprintf(stderr, "SDL_ttf error: %s\n", TTF_GetError());

	buttons_[0].text = menu_draw_text("Play", &buttons_[0].w, &buttons_[0].h);
	buttons_[0].rect = rect_create(window_width() / 2, window_height() - 75, 200, 50);
	buttons_[0].click = &menu_click_play;
}

void
menu_cleanup(void) {
	for (unsigned i = 0; i < NUM_MENU_BUTTONS; i++) {
		glDeleteTextures(1, &buttons_[i].text);
		rect_free(buttons_[i].rect);
	}

	TTF_CloseFont(font_);
	font_ = NULL;
	TTF_Quit();
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
	glBegin(GL_QUADS);
	for (int i = 0; i < NUM_MENU_BUTTONS; i++) {
		float x = buttons_[i].rect->x, y = buttons_[i].rect->y;
		float half_w = buttons_[i].rect->w / 2, half_h = buttons_[i].rect->h / 2;

		if (rect_contains_point(buttons_[i].rect, mouse_x, mouse_y)) {
			glColor3f(0.5, 0.1, 0.5);
		} else {
			glColor3f(0.2, 0.1, 0.5);
		}

		glVertex2f(x - half_w, y - half_h);
		glVertex2f(x + half_w, y - half_h);
		glVertex2f(x + half_w, y + half_h);
		glVertex2f(x - half_w, y + half_h);
	}
	glEnd();

	// Draw lables
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	for (int i = 0; i < NUM_MENU_BUTTONS; i++) {
		float x = buttons_[i].rect->x, y = buttons_[i].rect->y;
		int w = buttons_[i].w, h = buttons_[i].h;

		glBindTexture(GL_TEXTURE_2D, buttons_[i].text);
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

static GLuint
menu_draw_text(const char *text, int *w, int *h) {
	if (!font_)
		return 0;

	SDL_Color color = {0, 0, 0};
	SDL_Surface *surface = TTF_RenderText_Blended(font_, text, color);
	if (!surface)
		fprintf(stderr, "Could not print text: %s\n", TTF_GetError());

	*w = surface->w;
	*h = surface->h;

	glEnable(GL_TEXTURE_2D);

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, surface->pixels);

	glDisable(GL_TEXTURE_2D);

	SDL_FreeSurface(surface);

	return texture;
}

static void
menu_click_play(void) {
	states_queue_change(STATE_GAME);
}
