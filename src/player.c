#include "player.h"

void
player_init(void) {
}

void
player_cleanup(void) {
}

void
player_draw(void) {
	glColor3f(0.8f, 0.2f, 0.2f);

	glPushMatrix();
	glTranslatef(200.0f, 400.0f, 0.0f);

	glBegin(GL_QUADS);

	glVertex2f(-50.0f, -50.0f);
	glVertex2f( 50.0f, -50.0f);
	glVertex2f( 50.0f,  50.0f);
	glVertex2f(-50.0f,  50.0f);

	glEnd();
	glPopMatrix();
}
