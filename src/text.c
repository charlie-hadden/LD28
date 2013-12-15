#include "text.h"

static TTF_Font *big_;
static TTF_Font *main_;

static GLuint text_actually_write(const char *text, int *w, int *h, TTF_Font *font);

void
text_init(const char *font_path, int big_size, int main_size) {
	char error[512];
	if (TTF_Init() == -1) {
		snprintf(error, 512, "Could not initialize SDL_ttf: %s\n", TTF_GetError());
		die(error);
	}

	big_ = TTF_OpenFont(font_path, big_size);
	if (!big_) {
		snprintf(error, 512, "SDL_ttf error: %s\n", TTF_GetError());
		die(error);
	}

	main_ = TTF_OpenFont(font_path, main_size);
	if (!big_) {
		snprintf(error, 512, "SDL_ttf error: %s\n", TTF_GetError());
		die(error);
	}

	TTF_SetFontHinting(big_, TTF_HINTING_NONE);
	TTF_SetFontHinting(main_, TTF_HINTING_NONE);
}

void
text_cleanup() {
	TTF_CloseFont(big_);
	TTF_CloseFont(main_);
	big_ = main_ = NULL;
	TTF_Quit();
}

GLuint
text_write_big(const char *text, int *w, int *h) {
	if (!big_)
		return 0;

	return text_actually_write(text, w, h, big_);
}

GLuint
text_write(const char *text, int *w, int *h) {
	if (!main_)
		return 0;

	return text_actually_write(text, w, h, main_);
}

static GLuint
text_actually_write(const char *text, int *w, int *h, TTF_Font *font) {
	SDL_Color color = { 255, 255, 255 };
	SDL_Surface *surface = TTF_RenderText_Blended(font, text, color);
	if (!surface)
		fprintf(stderr, "Could not print text: %s\n", TTF_GetError());

	*w = surface->w;
	*h = surface->h;

	glEnable(GL_TEXTURE_2D);

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, surface->pixels);

	glDisable(GL_TEXTURE_2D);

	SDL_FreeSurface(surface);

	return texture;
}
