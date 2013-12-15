#include "enemy.h"

static enemy_t *enemies_[MAX_ENEMIES];
static unsigned count_ = 0;

static int target_enemies_;
static int spawn_rate_, spawn_cooldown_;

static void enemy_update_strafer(enemy_t *enemy);
static void enemy_bullets_strafer(enemy_t *enemy);

void
enemy_init(void) {
	target_enemies_ = 2;
	spawn_rate_ = 500;
	spawn_cooldown_ = 100;
}

void
enemy_cleanup(void) {
	for (unsigned i = 0; i < MAX_ENEMIES; i++) {
		enemy_free(enemies_[i]);
		enemies_[i] = NULL;
	}
	count_ = 0;
}

enemy_t*
enemy_create(void) {
	enemy_t *enemy = (enemy_t*)malloc(sizeof(enemy_t));
	return enemy;
}

void
enemy_free(enemy_t *enemy) {
	if (enemy) {
		rect_free(enemy->rect);
		free(enemy);
	}
}

enemy_t*
enemy_get(int index) {
	return enemies_[index];
}

void
enemy_set(int index, enemy_t *val) {
	if (!val)
		count_--;

	enemies_[index] = val;
}

void
enemy_check_bullet(rect_t *bullet, vec3 vel) {
	for (int i = 0; i < MAX_ENEMIES; i++) {
		enemy_t *enemy = enemies_[i];
		if (!enemy)
			continue;

		if (rect_collides(enemy->rect, bullet, vel)) {
			enemy_free(enemy);
			enemies_[i] = NULL;
			count_--;
		}
	}
}

void
enemy_spawn(enemy_t *enemy) {
	for (unsigned i = 0; i < MAX_ENEMIES; i++) {
		if (enemies_[i] == NULL) {
			enemies_[i] = enemy;
			count_++;
			return;
		}
	}

	printf("To many enemies\n");
}

void
enemy_update(void) {
	// Spawn new enemies if we need to

	// Loop through enemies
	//     Move
	//     spawn bullets

	spawn_cooldown_--;
	if (spawn_cooldown_ <= 0 && target_enemies_ * game_get_difficulty() > count_) {
		spawn_cooldown_ = spawn_rate_;

		float x = 100, y = 100;
		float size = 40;

		enemy_t *enemy = enemy_create();
		enemy->rect = rect_create(x, y, size, size);
		enemy->last_x_vel = 1.5f * game_get_difficulty();
		enemy->last_y_vel = 1.5f * game_get_difficulty();
		enemy->type = ENEMY_STRAFER;
		enemy->angle = 0;
		enemy->cooldown = rand() % 70;
		enemy->fire_rate = 100 + (rand() % 30 / 2);
		enemy_spawn(enemy);
	}

	for (int i = 0; i < MAX_ENEMIES; i++) {
		enemy_t *enemy = enemies_[i];
		if (!enemy)
			continue;

		switch (enemy->type) {
			case ENEMY_STRAFER:
				enemy_update_strafer(enemy);

				enemy->cooldown--;
				if (enemy->cooldown <= 0) {
					enemy->cooldown = enemy->fire_rate;
					enemy_bullets_strafer(enemy);
				}
				break;
		}
	}
}

static void
enemy_update_strafer(enemy_t *enemy) {
	enemy->rect->x += enemy->last_x_vel;

	if (enemy->rect->x < enemy->rect->w / 2 + 10) {
		enemy->rect->x = enemy->rect->w / 2 + 10;
		enemy->last_x_vel *= -1;
	}

	if (enemy->rect->x > window_width() - (enemy->rect->w / 2) - 10) {
		enemy->rect->x = window_width() - (enemy->rect->w / 2) - 10;
		enemy->last_x_vel *= -1;
	}
}

static void
enemy_bullets_strafer(enemy_t *enemy) {
	bullet_t *bullet = bullet_create();
	bullet->rect = rect_create(enemy->rect->x, enemy->rect->y + enemy->rect->h / 2, 20, 20);
	bullet->x_vel = 0.0f;
	bullet->y_vel = 2.0f;
	bullet->type = BULLET_SQUARE;
	bullet->player = false;
	bullet_spawn(bullet);
}

void
enemy_draw(void) {
	SDL_Color color = color_get(COLOR_ENEMY);
	glColor3f(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f);
	glBegin(GL_QUADS);

	for (int i = 0; i < MAX_ENEMIES; i++) {
		enemy_t *enemy = enemies_[i];
		if (!enemy)
			continue;

		float x = enemy->rect->x, y = enemy->rect->y;
		float w = enemy->rect->w / 2, h = enemy->rect->h / 2;

		glVertex2f(x - w, y - h);
		glVertex2f(x + w, y - h);
		glVertex2f(x + w, y + h);
		glVertex2f(x - w, y + h);
	}

	glEnd();
}
