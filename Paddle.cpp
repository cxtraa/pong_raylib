
#include <raylib.h>
#include <raymath.h>

#include "Paddle.h"
#include "Constants.h"

Paddle::Paddle(int player_number, double speed, int posX, int posY, int width, int height, Color color) {
	movementDirection = 0;
	this->speed = speed;
	pos.x = posX;
	pos.y = posY;
	this->width = width;
	this->height = height;
	this->color = color;
	this->player_number = player_number;
}

Paddle::Paddle() {}

void Paddle::update() {
	if (player_number == 1) {
		if (IsKeyDown(KEY_DOWN)) {
			movementDirection = -1;
			pos.y += speed * GetFrameTime();
		}
		else if (IsKeyDown(KEY_UP)) {
			movementDirection = 1;
			pos.y -= speed * GetFrameTime();
		}
		else {
			movementDirection = 0;
		}
	}
	else if (player_number == 2) {
		if (IsKeyDown(KEY_W)) {
			movementDirection = 1;
			pos.y -= speed * GetFrameTime();
		}
		else if (IsKeyDown(KEY_S)) {
			movementDirection = -1;
			pos.y += speed * GetFrameTime();
		}
		else {
			movementDirection = 0;
		}
	}

	pos.y = Clamp(pos.y, 0, screenHeight - paddleHeight);
}

void Paddle::draw() {
	Rectangle rect = Rectangle{ pos.x, pos.y, (float)width, (float)height };
	DrawRectangleRounded(rect, 6, 1, paddleColor);
}