#include "enemy.h"

static enemy_t *enemies_[MAX_ENEMIES];

void
enemy_init(void) {
}

void
enemy_cleanup(void) {
	for (unsigned i = 0; i < MAX_ENEMIES; i++) {
		enemy_free(enemies_[i]);
		enemies_[i] = NULL;
	}
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

void
enemy_spawn(enemy_t *enemy) {
	for (unsigned i = 0; i < MAX_ENEMIES; i++) {
		if (enemies_[i] == NULL) {
			enemies_[i] = enemy;
			return;
		}
	}

	printf("To many enemies\n");
}

void
enemy_update(unsigned int delta_time) {
}

void
enemy_draw(void) {
}
