#pragma once

#include <raylib.h>
#include "Paddle.h"
#include "Ball.h"
#include "Constants.h"
#include "State.h"
#include "Button.h"

/*

* Game class.

* Keeps track of state (title screen, main game, game over).
* Holds all the game objects (ball, paddle) as its member variables.
* Keeps track of score.
* Holds all game sounds.

*/ 

class Game {
public:
	int p1_score = 0;
	int p2_score = 0;
	State state;
	Button playButton;
	Button homeButton;

	Sound buttonSound;
	Sound hitSound;
	Sound scoreSound;

	Paddle p1_paddle;
	Paddle p2_paddle;
	Ball ball;

	Game();
	~Game();
	
	void draw();
	void update();
};