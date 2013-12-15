#include "window.h"

static SDL_Window *window_;
static SDL_GLContext context_;

static int width_, height_;

static rect_t *rect_;

void
window_init(const char *title, int width, int height) {
	width_ = width;
	height_ = height;

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

	rect_ = rect_create(width / 2, height / 2, width, height);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void
window_cleanup(void) {
	rect_free(rect_);
	SDL_GL_DeleteContext(context_);
	SDL_DestroyWindow(window_);
	SDL_Quit();
}

int
window_width(void) {
	return width_;
}

int
window_height(void) {
	return height_;
}

void
window_swap(void) {
	SDL_GL_SwapWindow(window_);
}

rect_t*
window_get_rect(void) {
	return rect_;
}

void
window_set_grab(bool grab) {
	SDL_SetWindowGrab(window_, grab);
}

void
window_warp_cursor(int x, int y) {
	SDL_WarpMouseInWindow(window_, x, y);
}
