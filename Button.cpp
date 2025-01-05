#include "Button.h"
#include "Constants.h"
#include <raylib.h>

// Implementation of Button class.

Button::Button(int posX, int posY, int width, int height, int textSize, const char* text) {
	this->posX = posX;
	this->posY = posY;
	this->width = width;
	this->height = height;
	this->text = text;
	this->textSize = textSize;
	bounds = Rectangle{ (float)posX, (float)posY, (float)width, (float)height };
	state = 0;
}

Button::Button() {}

void Button::update() {

	// Update the button state.
	Vector2 mousePosition = GetMousePosition();
	bool isHovering = CheckCollisionPointRec(mousePosition, bounds);
	bool isPressed = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

	// If the mouse is hovering and the button is pressed, goto state 2.
	// Otherwise, if its just hovering, goto state 1.
	// If neither hovering nor pressed, state 0.

	if (isHovering) {
		if (isPressed) {
			state = 2;
		}
		else {
			state = 1;
		}
	}
	else {
		state = 0;
	}
}

void Button::draw() {
	// Draw the correct look for the button.
	if (state == 0) {
		DrawRectangleRec(bounds, buttonNoHoverColor);
	}
	else if (state == 1) {
		DrawRectangleRec(bounds, buttonHoverColor);
	}
	else if (state == 2) {
		DrawRectangleRec(bounds, buttonPressedColor);
	}
	int textWidth = MeasureText(text, textSize);
	Vector2 textDimensions = MeasureTextEx(GetFontDefault(), text, textSize, 1.0f);
	DrawText(text, posX + (width - textWidth) / 2, posY + (height - textDimensions.y) / 2, textSize, buttonTextColor);
}