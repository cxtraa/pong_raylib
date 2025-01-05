#include <raylib.h>
#include <raymath.h>
#include <cmath>
#include <algorithm>
#include <iostream>
#include "Ball.h"
#include "Constants.h"
#include "Paddle.h"

Ball::Ball(int radius, Color color) {
	vel.x = 0;
	vel.y = 0;
	reset();
	lastResetTime = GetTime();
	this->radius = radius;
	this->color = color;
}

Ball::Ball() {}
 
void Ball::draw() {
	DrawCircle(pos.x, pos.y, radius, color);
}

void Ball::handle_paddle_collision(Sound& hitSound, Paddle& paddle) {
	// Check for top collision
	if (vel.y > 0 && pos.y + radius >= paddle.pos.y && pos.y - radius <= paddle.pos.y) {
		if (paddle.pos.x <= pos.x && pos.x <= paddle.pos.x + paddleWidth) {
			vel.y *= -1;
			PlaySound(hitSound);
		}
	}
	// Check for bottom collision
	if (vel.y < 0 && pos.y - radius <= paddle.pos.y + paddleHeight && pos.y + radius >= paddle.pos.y + paddleHeight) {
		if (paddle.pos.x <= pos.x && pos.x <= paddle.pos.x + paddleWidth) {
			vel.y *= -1;
			PlaySound(hitSound);
		}
	}
	// Check for right collision
	if (vel.x < 0 && pos.x - radius <= paddle.pos.x + paddleWidth && pos.x + radius >= paddle.pos.x + paddleWidth) {
		if (paddle.pos.y <= pos.y && pos.y <= paddle.pos.y + paddleHeight) {
			vel.x *= -1;
			// A part of the paddle velocity is imparted to the ball.
			if (paddle.movementDirection == 1) {
				vel.y -= paddleSpeed*TRANSFER_FRAC;
			}
			else if (paddle.movementDirection == -1) {
				vel.y += paddleSpeed*TRANSFER_FRAC;
			}
			PlaySound(hitSound);
		}
	}
	// Check for left collision
	if (vel.x > 0 && pos.x + radius >= paddle.pos.x && pos.x - radius <= paddle.pos.x) {
		if (paddle.pos.y <= pos.y && pos.y <= paddle.pos.y + paddleHeight) {
			vel.x *= -1;
			if (paddle.movementDirection == 1) {
				vel.y -= paddleSpeed*TRANSFER_FRAC;
			}
			else if (paddle.movementDirection == -1) {
				vel.y += paddleSpeed*TRANSFER_FRAC;
			}
			PlaySound(hitSound);
		}
	}
}

void Ball::handle_screen_collision(Sound& hitSound, Sound& scoreSound, int& p1_score, int& p2_score) {
	// Left side collision (point to player 2)
	if (vel.x < 0 && pos.x - radius <= 0) {
		reset();
		PlaySound(scoreSound);
		p2_score++;
	}
	// Right side collision (point to player 1)
	if (vel.x > 0 && pos.x + radius >= screenWidth) {
		reset();
		PlaySound(scoreSound);
		p1_score++;
	}

	// Top collision (bounce)
	if (vel.y < 0 && pos.y - radius <= 0) {
		PlaySound(hitSound);
		vel.y *= -1;
	}
	// Bottom collision (bounce)
	if (vel.y > 0 && pos.y + radius >= screenHeight) {
		PlaySound(hitSound);
		vel.y *= -1;
	}
}

void Ball::update(Sound& hitSound, Sound& scoreSound, int& p1_score, int& p2_score, Paddle& p1_paddle, Paddle& p2_paddle) {

	// Ball gets progressively faster
	vel.x *= k;
	vel.y *= k;

	// Movement
	if (GetTime() - lastResetTime >= waitInterval) {
		pos.x += vel.x * GetFrameTime();
		pos.y += vel.y * GetFrameTime();
	}

	// Collision handling
	handle_paddle_collision(hitSound, p1_paddle);
	handle_paddle_collision(hitSound, p2_paddle);
	handle_screen_collision(hitSound, scoreSound, p1_score, p2_score);
}

float Ball::uniform_rand(float min, float max) {
	// GetRandomValue() returns a random integer.
	// We exploit this to roughly generate a uniformly distributed variable.
	return min + (max - min) * GetRandomValue(0, RAND_MAX) / RAND_MAX;
}

void Ball::reset() {
	lastResetTime = GetTime();
	pos.x = screenWidth/2;
	pos.y = screenHeight/2;
	int rand = GetRandomValue(0, 3);
	float theta = 0;
	if (rand == 0) {
		theta = uniform_rand(0.524, 1.045); // pi/6 -> pi/3
	}
	else if (rand == 1) {
		theta = uniform_rand(2.094, 2.618); // 2pi/3 -> 5pi/6
	}
	else if (rand == 2) {
		theta = uniform_rand(-1.045, -0.524); // -pi/3 -> -pi/6
	}
	else if (rand == 3) {
		theta = uniform_rand(-2.618, -2.094); // -5pi/6 -> -2pi/3
	}

	float currSpeed = 0;
	// If the ball is stationary, start it with ballSpeed.
	// Otherwise, the ball speed is the magnitude of `vel`.
	if (vel.x != 0 || vel.y != 0) {
		currSpeed = std::sqrt(pow(vel.x, 2) + pow(vel.y, 2));
	}
	else {
		currSpeed = ballSpeed;
	}
	vel.x = currSpeed * std::cos(theta);
	vel.y = currSpeed * std::sin(theta);
}