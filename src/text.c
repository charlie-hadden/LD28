#include "text.h"

static TTF_Font *font_;

void
text_init(const char *font_path, int ptsize) {
	char error[512];
	if (TTF_Init() == -1) {
		snprintf(error, 512, "Could not initialize SDL_ttf: %s\n", TTF_GetError());
		die(error);
	}

	font_ = TTF_OpenFont(font_path, ptsize);
	if (!font_) {
		snprintf(error, 512, "SDL_ttf error: %s\n", TTF_GetError());
		die(error);
	}

	TTF_SetFontHinting(font_, TTF_HINTING_NONE);
}

void
text_cleanup() {
	TTF_CloseFont(font_);
	font_ = NULL;
	TTF_Quit();
}

GLuint
text_write(const char *text, int *w, int *h) {
	if (!font_)
		return 0;

	SDL_Color color = { 255, 255, 255 };
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
