#include "common.h"
#include "window.h"
#include "states.h"

static void init(void);
static void cleanup(void);

static void handle_event(SDL_Event *event);
static void update(unsigned int delta_time);
static void draw(void);

int main(int argc, const char *argv[]) {
	init();

	bool running = true;
	SDL_Event event;
	unsigned int last_time = 0, current_time, delta_time;
	unsigned int last_fps_time = 0, frames = 0;

	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				running = false;

			handle_event(&event);
		}

		current_time = SDL_GetTicks();
		delta_time = current_time - last_time;
		last_time = current_time;

		frames++;
		if (current_time >= last_fps_time + 1000) {
			printf("%u FPS\n", frames);
			frames = 0;
			last_fps_time = current_time;
		}

		update(delta_time);
		draw();
	}

	cleanup();
	return EXIT_SUCCESS;
}

static void
init(void) {
	window_init("You only get one", 600, 800);

	glOrtho(0.0, 600.0, 800.0, 0.0, -1, 1);

	states_init();
}

static void
cleanup(void) {
	states_cleanup();
	window_cleanup();
}

static void
handle_event(SDL_Event *event) {
	state_t *state = states_get_state();
	if (state->handle_event)
		state->handle_event(event);
}

static void
update(unsigned int delta_time) {
	states_update();

	state_t *state = states_get_state();
	if (state->update)
		state->update(delta_time);
}

static void
draw(void) {
	glClearColor(0.2f, 0.2f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	state_t *state = states_get_state();
	if (state->draw)
		state->draw();

	window_swap();
}
