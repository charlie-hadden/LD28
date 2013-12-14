#include "bullet.h"

static vector_t *bullets_;

void
bullet_init(void) {
	bullets_ = vector_create();
}

void
bullet_cleanup(void) {
	for (unsigned i = 0; i < vector_count(bullets_); i++) {
		bullet_free(vector_get(bullets_, i));
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
	rect_free(bullet->rect);
	free(bullet);
}

void
bullet_spawn(bullet_t *bullet) {
	vector_add(bullets_, bullet);
}

void
bullet_update(unsigned int delta_time) {
	rect_t *player = player_get_rect();

	for (unsigned i = 0; i < vector_count(bullets_); i++) {
		bullet_t *bullet = vector_get(bullets_, i);
		bullet->rect->x += bullet->x_vel * delta_time;
		bullet->rect->y += bullet->y_vel * delta_time;

		if (rect_intersecting(player, bullet->rect)) {
			printf("Intersecting\n");
		}
	}
}

void
bullet_draw(void) {
	glColor3f(0.2f, 0.8f, 0.2f);
	glPointSize(5.0f);
	glBegin(GL_POINTS);

	for (unsigned i = 0; i < vector_count(bullets_); i++) {
		bullet_t *bullet = vector_get(bullets_, i);

		glVertex2f(bullet->rect->x, bullet->rect->y);
	}

	glEnd();
}
