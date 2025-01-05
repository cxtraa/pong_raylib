#pragma once

#include <raylib.h>
#include "Paddle.h"

/*
* Ball class.
* 
* Updates its own velocity.
* Checks for collisions with screen boundaries.
* Checks for collisions with paddle.
* Plays sound effects (passed as arguments from Game instance).
*/

class Ball {
public:
	Vector2 pos;
	Vector2 vel;
	Color color;
	int radius;
	float lastResetTime; // Each time a player scores, we record that as the last reset time. Then the game waits for `waitInterval` seconds (defined in Constants.h) before starting.

	Ball(int radius, Color color);
	Ball();

	void draw();
	void update(Sound& hitSound, Sound& scoreSound, int& p1_score, int& p2_score, Paddle& p1_paddle, Paddle& p2_paddle);

	// Change ball velocity for paddle collision + play sounds.
	void handle_paddle_collision(Sound& hitSound, Paddle& paddle);

	// Change ball velocity to account for collision with screen boundaries + play sounds.
	void handle_screen_collision(Sound& hitSound, Sound& scoreSound, int& p1_score, int& p2_score);

	// Reset ball to centre after a point, shoot out ball in random direction.
	void reset();

	// Generates a uniform random value between `min`, `max`.
	float uniform_rand(float min, float max);
};;