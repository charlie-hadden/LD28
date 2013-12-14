#include "common.h"
#include "window.h"
#include "player.h"

static void init(void);
static void cleanup(void);

static void handle_event(SDL_Event *event);
static void update(void);
static void draw(void);

int main(int argc, const char *argv[]) {
	init();

	bool running = true;
	SDL_Event event;

	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				running = false;

			handle_event(&event);
		}

		update();
		draw();
	}

	cleanup();
	return EXIT_SUCCESS;
}

static void
init(void) {
	window_init("You only get one", 600, 800);

	glOrtho(0.0, 600.0, 800.0, 0.0, -1, 1);

	player_init();
}

static void
cleanup(void) {
	window_cleanup();
	player_cleanup();
}

static void
handle_event(SDL_Event *event) {
}

static void
update(void) {
}

static void
draw(void) {
	glClearColor(0.2f, 0.2f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	player_draw();

	window_swap();
}
