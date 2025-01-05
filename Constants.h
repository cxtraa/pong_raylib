#pragma once
#include <raylib.h>
#include <cmath>

/*
* Constants.
* All constant values used throughout the game.
*/

// Timings
const float waitInterval = 2.0; // Time to wait after point scored

// Screen bounds constants
const int screenWidth = 1280;
const int screenHeight = 720;

// Paddle dimensions
const int paddleWidth = 20;
const int paddleHeight = 100;

// Ball dimensions
const int ballRadius = 10;

// Velocities
const double paddleSpeed = 500;
const double ballSpeed = 300;
const double TRANSFER_FRAC = 0.5; // fraction of paddle velocity transferred to ball in collision

// Colors
const Color paddleColor = Color{ 255, 255, 255, 255 };
const Color bgColor = Color{ 0, 0, 0, 255 };
const Color ballColor = Color{ 255, 255, 255, 255 };
const Color textColor = Color{ 255, 255, 255, 255 };
const Color buttonTextColor = Color{ 0, 0, 0, 255 };
const Color buttonNoHoverColor = Color{ 255, 255, 255, 255 };
const Color buttonHoverColor = Color{ 200, 200, 200, 255 };
const Color buttonPressedColor = Color{ 150, 150, 150, 255 };

// Font sizes
const int scoreTextSize = 100;
const int titleSize = 100;

// Scores
const int maxScore = 5;

// Button dimensions
const int buttonWidth = 150;
const int buttonHeight = 75;

// Ball speed control
const float T = 60; // Ball speed doubles every T seconds
const int FPS = 60;
const float k = pow(2, 1 / (T * FPS)); // The factor by which ball velocity components are multiplied every frame.