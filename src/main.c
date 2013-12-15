#include <time.h>
#include "common.h"
#include "window.h"
#include "states.h"

static void init(void);
static void cleanup(void);

static void handle_event(SDL_Event *event);
static void update();
static void draw(void);

int main(int argc, char *argv[]) {
	srand(time(NULL));

	init();

	bool running = true;
	SDL_Event event;

	uint64_t last_time = SDL_GetTicks(), current_time, delta_time;
	double ms_per_update = 1000.0f / 144, unprocessed = 0;
	unsigned int readout_time = 0, updates = 0, frames = 0;

	while (running) {
		current_time = SDL_GetTicks();
		delta_time = current_time - last_time;
		last_time = current_time;

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				running = false;

			handle_event(&event);
		}

		unprocessed += delta_time / ms_per_update;
		while (unprocessed >= 1) {
			update();
			updates++;
			unprocessed -= 1;
		}

		update(delta_time);
		draw();
		frames++;

		if (current_time >= readout_time + 1000) {
			printf("%u Updates, %u FPS\n", updates, frames);
			updates = frames = 0;
			readout_time = current_time;
		}

		int frame_time = ms_per_update - (SDL_GetTicks() - current_time);
		if (frame_time > 0)
			SDL_Delay(frame_time);
	}

	cleanup();
	return EXIT_SUCCESS;
}

static void
init(void) {
	window_init("You only get one", 600, 800);
	text_init("assets/onyx.ttf", 28);
	color_init();

	glOrtho(0.0, 600.0, 800.0, 0.0, -1, 1);

	states_init();
}

static void
cleanup(void) {
	states_cleanup();
	text_cleanup();
	window_cleanup();
}

static void
handle_event(SDL_Event *event) {
	state_t *state = states_get_state();
	if (state->handle_event)
		state->handle_event(event);
}

static void
update(void) {
	states_update();

	state_t *state = states_get_state();
	if (state->update)
		state->update();
}

static void
draw(void) {
	SDL_Color color = color_get(COLOR_BASE);
	glClearColor(color.r / 254.0f, color.g / 254.0f, color.b / 254.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	state_t *state = states_get_state();
	if (state->draw)
		state->draw();

	window_swap();
}
