#include "bullet.h"

static bullet_t *bullets_[MAX_BULLETS];

static void bullet_draw_square(void);
static void bullet_draw_round(void);

void
bullet_init(void) {
}

void
bullet_cleanup(void) {
	for (unsigned i = 0; i < MAX_BULLETS; i++) {
		bullet_free(bullets_[i]);
		bullets_[i] = NULL;
	}
}

bullet_t*
bullet_create(void) {
	bullet_t *bullet = (bullet_t*)malloc(sizeof(bullet_t));
	return bullet;
}

void
bullet_free(bullet_t *bullet) {
	if (bullet) {
		rect_free(bullet->rect);
		free(bullet);
	}
}

void
bullet_spawn(bullet_t *bullet) {
	for (unsigned i = 0; i < MAX_BULLETS; i++) {
		if (bullets_[i] == NULL) {
			bullets_[i] = bullet;
			return;
		}
	}

	printf("Too many bullets!\n");
}

void
bullet_update(unsigned int delta_time) {
	rect_t *player = player_get_rect();
	rect_t *window = window_get_rect();

	for (unsigned i = 0; i < MAX_BULLETS; i++) {
		bullet_t *bullet = bullets_[i];
		if (bullet == NULL)
			continue;

		if (!rect_intersecting(window, bullet->rect)) {
			bullets_[i] = NULL;
			bullet_free(bullet);
			continue;
		}

		bullet->rect->x += bullet->x_vel * delta_time;
		bullet->rect->y += bullet->y_vel * delta_time;

		if (!bullet->player && rect_intersecting(player, bullet->rect)) {
			bullets_[i] = NULL;
			bullet_free(bullet);
			game_gameover();
			break;
		}
	}
}

void
bullet_draw(void) {
	bullet_draw_square();
	bullet_draw_round();
}

static void
bullet_draw_square(void) {
	glColor3f(0.8f, 0.2f, 0.2f);
	glBegin(GL_QUADS);

	for (unsigned i = 0; i < MAX_BULLETS; i++) {
		bullet_t *bullet = bullets_[i];

		if (!bullet || bullet->type != BULLET_SQUARE)
			continue;

		float x = bullet->rect->x, y = bullet->rect->y;
		float half_w = bullet->rect->w / 2, half_h = bullet->rect->h / 2;

		glVertex2f(x - half_w, y - half_h);
		glVertex2f(x + half_w, y - half_h);
		glVertex2f(x + half_w, y + half_h);
		glVertex2f(x - half_w, y + half_h);
	}

	glEnd();
}

static void
bullet_draw_round(void) {
	glColor3f(0.6f, 0.1f, 0.1f);
	glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);

	for (unsigned i = 0; i < MAX_BULLETS; i++) {
		bullet_t *bullet = bullets_[i];

		if (!bullet || bullet->type != BULLET_ROUND)
			continue;

		glPointSize((bullet->rect->w + bullet->rect->h) / 2);
		glVertex2f(bullet->rect->x, bullet->rect->y);
	}

	glEnd();
	glDisable(GL_POINT_SMOOTH);
}

void
bullet_check_collisions(rect_t *rect) {
	for (unsigned i = 0; i < MAX_BULLETS; i++) {
		bullet_t *bullet = bullets_[i];

		if (bullet == NULL)
			continue;

		if (!bullet->player && rect_intersecting(rect, bullet->rect)) {
			bullets_[i] = NULL;
			bullet_free(bullet);
			game_gameover();
			break;
		}
	}
}
