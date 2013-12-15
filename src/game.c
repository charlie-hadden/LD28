#include "game.h"

static float difficulty_ = 1.0;
static bool game_over_ = false;

static unsigned int start_time_, score_;
static GLuint score_text_;
static int score_w_, score_h_;

static GLuint game_, over_, space_, cont_;
static int game_w_, game_h_, over_w_, over_h_, space_w_, space_h_, cont_w_, cont_h_;

void
game_init(void) {
	start_time_ = 0;
	score_ = 0;

	game_over_ = false;
	enemy_init();
	bullet_init();
	player_init();
	SDL_ShowCursor(false);

	game_ = text_write_big("GAME", &game_w_, &game_h_);
	over_ = text_write_big("OVER", &over_w_, &over_h_);
	space_ = text_write("PRESS SPACE", &space_w_, &space_h_);
	cont_ = text_write("TO CONTINUE", &cont_w_, &cont_h_);

	score_text_ = text_write("SCORE: ", &score_w_, &score_h_);
}

void
game_cleanup(void) {
	enemy_cleanup();
	bullet_cleanup();
	player_cleanup();
	SDL_ShowCursor(true);

	glDeleteTextures(1, &game_);
	glDeleteTextures(1, &over_);
	glDeleteTextures(1, &space_);
	glDeleteTextures(1, &cont_);
	glDeleteTextures(1, &score_text_);
}

void
game_handle_event(SDL_Event *event) {
}

void
game_update(void) {
	const uint8_t *keys = SDL_GetKeyboardState(NULL);
	if (game_over_ && keys[SDL_SCANCODE_SPACE])
		states_queue_change(STATE_MENU);

	window_set_grab(!game_over_);

	if (!start_time_) {
		start_time_ = SDL_GetTicks();
	} else if (!game_over_) {
		score_ = (SDL_GetTicks() - start_time_) / 10;
		char score[128];
		snprintf(score, 128, "SCORE: %u", score_);
		text_rewrite(score_text_, score, &score_w_, &score_h_);
	}

	if (!game_over_) {
		color_update();
		bullet_update();
		enemy_update();
		player_update();
	}
}

void
game_draw(void) {
	bullet_draw();
	enemy_draw();
	player_draw();

	SDL_Color bc = color_get(COLOR_BASE);
	if (bc.r * 0.299 + bc.g * 0.587 + bc.b * 0.114 > 186) {
		glColor3f(0, 0, 0);
	} else {
		glColor3f(1, 1, 1);
	}

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, score_text_);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex2f(20 + score_w_ / 2 - score_w_ / 2, 30 - score_h_ / 2);
	glTexCoord2f(1, 0);
	glVertex2f(20 + score_w_ / 2 + score_w_ / 2, 30 - score_h_ / 2);
	glTexCoord2f(1, 1);
	glVertex2f(20 + score_w_ / 2 + score_w_ / 2, 30 + score_h_ / 2);
	glTexCoord2f(0, 1);
	glVertex2f(20 + score_w_ / 2 - score_w_ / 2, 30 + score_h_ / 2);
	glEnd();

	if (game_over_) {
		float off_x = window_width() / 2, off_y = 200;

		glBindTexture(GL_TEXTURE_2D, game_);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex2f(off_x - game_w_ / 2, off_y - game_h_ / 2);
		glTexCoord2f(1, 0);
		glVertex2f(off_x + game_w_ / 2, off_y - game_h_ / 2);
		glTexCoord2f(1, 1);
		glVertex2f(off_x + game_w_ / 2, off_y + game_h_ / 2);
		glTexCoord2f(0, 1);
		glVertex2f(off_x - game_w_ / 2, off_y + game_h_ / 2);
		glEnd();

		off_y += 60;
		glBindTexture(GL_TEXTURE_2D, over_);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex2f(off_x - over_w_ / 2, off_y - over_h_ / 2);
		glTexCoord2f(1, 0);
		glVertex2f(off_x + over_w_ / 2, off_y - over_h_ / 2);
		glTexCoord2f(1, 1);
		glVertex2f(off_x + over_w_ / 2, off_y + over_h_ / 2);
		glTexCoord2f(0, 1);
		glVertex2f(off_x - over_w_ / 2, off_y + over_h_ / 2);
		glEnd();

		off_y = window_height() - 200;
		glBindTexture(GL_TEXTURE_2D, space_);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex2f(off_x - space_w_ / 2, off_y - space_h_ / 2);
		glTexCoord2f(1, 0);
		glVertex2f(off_x + space_w_ / 2, off_y - space_h_ / 2);
		glTexCoord2f(1, 1);
		glVertex2f(off_x + space_w_ / 2, off_y + space_h_ / 2);
		glTexCoord2f(0, 1);
		glVertex2f(off_x - space_w_ / 2, off_y + space_h_ / 2);
		glEnd();

		off_y += 30;
		glBindTexture(GL_TEXTURE_2D, cont_);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex2f(off_x - cont_w_ / 2, off_y - cont_h_ / 2);
		glTexCoord2f(1, 0);
		glVertex2f(off_x + cont_w_ / 2, off_y - cont_h_ / 2);
		glTexCoord2f(1, 1);
		glVertex2f(off_x + cont_w_ / 2, off_y + cont_h_ / 2);
		glTexCoord2f(0, 1);
		glVertex2f(off_x - cont_w_ / 2, off_y + cont_h_ / 2);
		glEnd();

	}

	glDisable(GL_TEXTURE_2D);
}

float
game_get_difficulty(void) {
	return difficulty_;
}

void
game_set_difficulty(float difficulty) {
	difficulty_ = difficulty;
}

void
game_gameover(void) {
	game_over_ = true;
}
