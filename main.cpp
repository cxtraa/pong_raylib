#include <raylib.h>
#include "Game.h"
#include "Constants.h"

int main() {

	InitWindow(screenWidth, screenHeight, "Pong");
	SetTargetFPS(FPS);

	Game game = Game();
	
	while (!WindowShouldClose()) {
		BeginDrawing();

		game.draw();
		game.update();

		EndDrawing();
	}

	CloseWindow();
}