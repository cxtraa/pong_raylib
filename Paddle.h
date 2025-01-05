#pragma once
#include <raylib.h>

/*
* Paddle class.
* 
* Manages movement of paddle.
*/

class Paddle {
public:
	double speed;
	int width;
	int height;
	int player_number;
	int movementDirection; // 1 = up, 0 = stationary, -1 = down.
	Color color;
	Vector2 pos;

	Paddle(int player_number, double speed, int posX, int posY, int width, int height, Color color);
	Paddle();

	void draw();
	void update();
};