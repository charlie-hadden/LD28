#include "player.h"

static int x_ = 0, y_ = 0;
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
