#include "player.h"

static float x_ = 0, y_ = 0;
static int size_ = 0;

void
player_init(void) {
	x_ = 300;
	y_ = 600;
	size_ = 50;
}

void
player_cleanup(void) {
}

void
player_update(unsigned int delta_time) {
	int mouse_x, mouse_y;
	SDL_GetMouseState(&mouse_x, &mouse_y);

	x_ = mouse_x;
	y_ = mouse_y;
}

void
player_draw(void) {
	glColor3f(0.8f, 0.2f, 0.2f);

	glPushMatrix();
	glTranslatef(x_, y_, 0.0f);

	glBegin(GL_QUADS);

	glVertex2f(-size_ / 2, -size_ / 2);
	glVertex2f( size_ / 2, -size_ / 2);
	glVertex2f( size_ / 2,  size_ / 2);
	glVertex2f(-size_ / 2,  size_ / 2);

	glEnd();
	glPopMatrix();
}
