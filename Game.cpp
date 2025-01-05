
#include <raylib.h>
#include <raymath.h>

#include "Game.h"
#include "Ball.h"
#include "Paddle.h"
#include "Constants.h"
#include "State.h"
#include "Button.h"

Game::Game() {
	state = TITLE_SCREEN;
	playButton = Button((screenWidth - buttonWidth)/2, 400, buttonWidth, buttonHeight, 40, "Play");
	homeButton = Button((screenWidth - buttonWidth) / 2, 400, buttonWidth, buttonHeight, 40, "Home");

	InitAudioDevice();
	hitSound = LoadSound("audio/ballCollision.wav");
	scoreSound = LoadSound("audio/playerScore.wav");
	buttonSound = LoadSound("audio/selectButton.wav");
}

Game::~Game() {
	UnloadSound(hitSound);
	UnloadSound(scoreSound);
	UnloadSound(buttonSound);
	CloseAudioDevice();
}

void Game::draw() {
	if (state == GAME) {
		ball.draw();
		p1_paddle.draw();
		p2_paddle.draw();

		// Draw score
		const char* p1_score_text = TextFormat("%i", p1_score);
		const char* p2_score_text = TextFormat("%i", p2_score);
		int p1_width = MeasureText(p1_score_text, scoreTextSize);
		int p2_width = MeasureText(p2_score_text, scoreTextSize);
		DrawText(p1_score_text, (screenWidth / 2 - p1_width) / 2, 60, scoreTextSize, textColor);
		DrawText(p2_score_text, screenWidth / 2 + ((screenWidth / 2) - p2_width) / 2, 60, scoreTextSize, textColor);
	}
	else if (state == TITLE_SCREEN) {
		const char* title = "Pong";
		int titleWidth = MeasureText(title, titleSize);
		DrawText(title, (screenWidth - titleWidth) / 2, 250, titleSize, textColor);
		playButton.draw();
	}
	else {
		homeButton.draw();
		if (state == P1_WINNER) {
			const char* text = "P1 wins!";
			int textWidth = MeasureText(text, titleSize);
			DrawText(text, (screenWidth - textWidth) / 2, 250, titleSize, textColor);
		}
		else if (state == P2_WINNER) {
			const char* text = "P2 wins!";
			int textWidth = MeasureText(text, titleSize);
			DrawText(text, (screenWidth - textWidth) / 2, 250, titleSize, textColor);
		}
	}

	ClearBackground(bgColor);
}

void Game::update() {

	if (state == TITLE_SCREEN) {
		playButton.update();
		if (playButton.state == 2 || IsKeyPressed(KEY_ENTER)) {
			PlaySound(buttonSound);
			state = GAME;
			ball = Ball(ballRadius, ballColor);
			p1_paddle = Paddle(1, paddleSpeed, 50, (screenHeight - paddleHeight) / 2, paddleWidth, paddleHeight, paddleColor);
			p2_paddle = Paddle(2, paddleSpeed, screenWidth - 50 - paddleWidth, (screenHeight - paddleHeight) / 2, paddleWidth, paddleHeight, paddleColor);
		}
	}
	else if (state == GAME) {
		p1_paddle.update();
		p2_paddle.update();
		ball.update(hitSound, scoreSound, p1_score, p2_score, p1_paddle, p2_paddle);
		if (p1_score == maxScore) {
			state = P1_WINNER;
			p1_score = 0;
			p2_score = 0;
		}
		else if (p2_score == maxScore) {
			state = P2_WINNER;
			p1_score = 0;
			p2_score = 0;
		}
	}
	else {
		homeButton.update();
		if (homeButton.state == 2) {
			PlaySound(buttonSound);
			state = TITLE_SCREEN;
		}
	}
}