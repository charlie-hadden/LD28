#include "player.h"

static float x_ = 0, y_ = 0;
static int size_ = 0;
static rect_t *rect_;

static bool using_keyboard_ = true;
static int last_mouse_x_, last_mouse_y_;

static int fire_time = 100, fire_cooldown = 0;

static void fire(void);

void
player_init(void) {
	x_ = 300;
	y_ = 600;
	size_ = 30;

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
	const uint8_t *state = SDL_GetKeyboardState(NULL);

	if (!last_mouse_x_ && !last_mouse_y_) {
		last_mouse_x_ = mouse_x;
		last_mouse_y_ = mouse_y;
	}

	vec3 vel = { 0, 0, 0 };

	if (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP])
		vel[1] -= 1;

	if (state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN])
		vel[1] += 1;

	if (state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT])
		vel[0] -= 1;

	if (state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT])
		vel[0] += 1;

	if (vec3_len(vel)) {
		using_keyboard_ = true;
		vec3_norm(vel, vel);
	} else if ((mouse_x != x_ || mouse_y != y_)
			&& (mouse_x != last_mouse_x_ || mouse_y != last_mouse_y_ || !using_keyboard_)) {
		using_keyboard_ = false;
		last_mouse_x_ = mouse_x;
		last_mouse_y_ = mouse_y;
		vel[0] = mouse_x - x_;
		vel[1] = mouse_y - y_;
		vec3_norm(vel, vel);
	}

	vec3_scale(vel, vel, 0.8 * delta_time);

	if (state[SDL_SCANCODE_LSHIFT] || state[SDL_SCANCODE_RSHIFT])
		vec3_scale(vel, vel, 0.6);

	rect_t *rect = player_get_rect();
	bullet_check_collisions(rect, vel);

	x_ += vel[0];
	y_ += vel[1];

	float mouse_dist = sqrt((mouse_x - x_) * (mouse_x - x_) + (mouse_y - y_) * (mouse_y - y_));
	if (!using_keyboard_ && mouse_dist < 2) {
		x_ = mouse_x;
		y_ = mouse_y;
	}

	if (x_ - size_ / 2 < 0)
		x_ = size_ / 2;

	if (x_ + size_ / 2 >= window_width())
		x_ = window_width() - size_ / 2;

	if (y_ - size_ / 2 < 0)
		y_ = size_ / 2;

	if (y_ + size_ / 2 >= window_height())
		y_ = window_height() - size_ / 2;

	fire_cooldown -= delta_time;
	if (fire_cooldown <= 0) {
		fire();
		fire_cooldown = fire_time;
	}
}

void
player_draw(void) {
	// Draw the cursor
	if (!using_keyboard_) {
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
