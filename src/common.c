#include "common.h"

void
die(const char *msg) {
	fprintf(stderr, "%s: %s\n", msg, SDL_GetError());
	SDL_Quit();
	exit(EXIT_FAILURE);
}
