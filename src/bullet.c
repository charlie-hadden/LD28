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
			vector_delete(bullets_, i);
			bullet_free(bullet);
		}
	}
}

void
bullet_draw(void) {
	glColor3f(0.2f, 0.8f, 0.2f);
	glBegin(GL_QUADS);

	for (unsigned i = 0; i < vector_count(bullets_); i++) {
		bullet_t *bullet = vector_get(bullets_, i);

		float x = bullet->rect->x, y = bullet->rect->y;
		float half_w = bullet->rect->w / 2, half_h = bullet->rect->h / 2;

		glVertex2f(x - half_w, y - half_h);
		glVertex2f(x + half_w, y - half_h);
		glVertex2f(x + half_w, y + half_h);
		glVertex2f(x - half_w, y + half_h);
	}

	glEnd();
}
