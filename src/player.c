#include "player.h"

static float x_ = 0, y_ = 0;
static int size_ = 0;
static rect_t *rect_;

static int fire_time = 100, fire_cooldown = 0;

static void fire(void);

void
player_init(void) {
	x_ = 300;
	y_ = 600;
	size_ = 50;

	rect_ = rect_create(0, 0, 0, 0);

	SDL_ShowCursor(0);
}

void
player_cleanup(void) {
	free(rect_);

	SDL_ShowCursor(1);
}

void
player_update(unsigned int delta_time) {
	int mouse_x, mouse_y;
	SDL_GetMouseState(&mouse_x, &mouse_y);

	vec3 vel = { mouse_x - x_, mouse_y - y_, 0 };
	if (vec3_len(vel)) {
		vec3_norm(vel, vel);
		vec3_scale(vel, vel, 0.8 * delta_time);
		x_ += vel[0];
		y_ += vel[1];
	}

	fire_cooldown -= delta_time;
	if (fire_cooldown <= 0) {
		fire();
		fire_cooldown = fire_time;
	}
}

void
player_draw(void) {
	// Draw the player
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

	// Draw the cursor
	int mouse_x, mouse_y;
	SDL_GetMouseState(&mouse_x, &mouse_y);
	glEnable(GL_POINT_SMOOTH);
	glPointSize(10);
	glColor3f(0.1, 0.7, 0.1);
	glBegin(GL_POINTS);
	glVertex2f(mouse_x, mouse_y);
	glEnd();
	glDisable(GL_POINT_SMOOTH);
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
	bullet_t *bullet = bullet_create();
	bullet->rect = rect_create(x_, y_ - size_ / 2, 10, 10);
	bullet->x_vel = 0;
	bullet->y_vel = -0.4f;
	bullet->player = true;
	bullet->type = BULLET_SQUARE;

	bullet_spawn(bullet);
}
