#include "bullet.h"

static vector_t *bullets_;

void
bullet_init(void) {
	bullets_ = vector_create();
}

void
bullet_cleanup(void) {
	for (unsigned i = 0; i < vector_count(bullets_); i++) {
		free(vector_get(bullets_, i));
	}

	vector_free(bullets_);
}

bullet_t*
bullet_create(void) {
	bullet_t *bullet = (bullet_t*)malloc(sizeof(bullet_t));
	return bullet;
}

void
bullet_free(bullet_t *bullet) {
	free(bullet);
}

void
bullet_spawn(bullet_t *bullet) {
	vector_add(bullets_, bullet);
}

void
bullet_draw(void) {
	glColor3f(0.2f, 0.8f, 0.2f);
	glBegin(GL_POINTS);

	for (unsigned i = 0; i < vector_count(bullets_); i++) {
		bullet_t *bullet = vector_get(bullets_, i);

		glVertex2f(bullet->x_pos, bullet->y_pos);
	}

	glEnd();
}
