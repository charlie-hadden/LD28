#include "player.h"

static float x_ = 0, y_ = 0;
static int size_ = 0;
static rect_t *rect_;

static int fire_time = 200, fire_cooldown = 0;

static void fire(void);

void
player_init(void) {
	x_ = 300;
	y_ = 600;
	size_ = 50;

	rect_ = rect_create(0, 0, 0, 0);
}

void
player_cleanup(void) {
	free(rect_);
}

void
player_update(unsigned int delta_time) {
	int mouse_x, mouse_y;
	SDL_GetMouseState(&mouse_x, &mouse_y);

	x_ = mouse_x;
	y_ = mouse_y;

	fire_cooldown -= delta_time;
	if (fire_cooldown <= 0) {
		fire();
		fire_cooldown = fire_time;
	}
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

rect_t*
player_get_rect(void) {
	rect_->x = x_;
	rect_->y = y_;
	rect_->w = size_;
	rect_->h = size_;

	return rect_;
}

static void
fire(void) {
	printf("Fire\n");

	bullet_t *bullet = bullet_create();
	bullet->rect = rect_create(500, 400, 10, 10);
	bullet->x_vel = 0;
	bullet->y_vel = -0.1f;
	bullet->type = BULLET_SQUARE;

	bullet_spawn(bullet);
}
