#include "window.h"

static SDL_Window *window_;
static SDL_GLContext context_;

void
window_init(const char *title, int width, int height) {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		die("Failed to initialize SDL");

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	window_ = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
	if (!window_)
		die("Could not create window");

	context_ = SDL_GL_CreateContext(window_);
	if (!context_)
		die("Could not create GL context");

	GLenum glew_status = glewInit();
	if (glew_status != GLEW_OK)
		die("Could not initialize GLEW");

	SDL_GL_SetSwapInterval(-1);
}

void
window_cleanup(void) {
	SDL_GL_DeleteContext(context_);
	SDL_DestroyWindow(window_);
	SDL_Quit();
}

void
window_swap(void) {
	SDL_GL_SwapWindow(window_);
}
