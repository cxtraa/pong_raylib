#pragma once
#include <raylib.h>

// Button class template.
// Changes color when hovered on, and manages state using `state`.

class Button {
public:
	int posX;
	int posY;
	int width;
	int height;
	Rectangle bounds;
	int textSize;
	const char* text;
	int state; // 0 = unhovered, 1 = hovered, 2 = pressed

	Button(int posX, int posY, int width, int height, int textSize, const char* text);
	Button();

	void update();
	void draw();
};