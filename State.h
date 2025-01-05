#pragma once

/*
* Records game state.
* 
* `TITLE_SCREEN` - state for title_screen.
* `GAME` - state when users are playing.
* `P1_WINNER` - state when player 1 has won.
* `P2_WINNER` - state when player 2 has won.
*/

enum State {
	TITLE_SCREEN,
	GAME,
	P1_WINNER,
	P2_WINNER,
};