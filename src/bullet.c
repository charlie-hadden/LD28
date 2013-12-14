#include "bullet.h"

static bullet_t *bullets_[MAX_BULLETS];

void
bullet_init(void) {
}

void
bullet_cleanup(void) {
	for (unsigned i = 0; i < MAX_BULLETS; i++) {
		bullet_free(bullets_[i]);
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

		// We can kind of cheat here and use a collision rectangle that fits
		// both the start and the destination to stop clipping through.
		float x = bullet->rect->x, y = bullet->rect->y;
		int w = bullet->rect->w, h = bullet->rect->h;

		float dist_x = bullet->x_vel * delta_time;
		float dist_y = bullet->y_vel * delta_time;

		// Set up the rectangle to check for the collision
		bullet->rect->x += dist_x;
		bullet->rect->y += dist_y;
		bullet->rect->w = sqrt(w*w + h*h);
		bullet->rect->h = sqrt(w*w + h*h);


		if (!bullet->player && rect_intersecting(player, bullet->rect)) {
			bullets_[i] = NULL;
			bullet_free(bullet);
			break;
		}

		// Now we can reset the rectangle
		bullet->rect->x = x + dist_x;
		bullet->rect->y = y + dist_y;
		bullet->rect->w = w;
		bullet->rect->h = h;
	}
}

void
bullet_draw(void) {
	glColor3f(0.2f, 0.8f, 0.2f);
	glBegin(GL_QUADS);

	for (unsigned i = 0; i < MAX_BULLETS; i++) {
		bullet_t *bullet = bullets_[i];
		if (bullet == NULL)
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
