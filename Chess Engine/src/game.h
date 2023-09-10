#pragma once
#include "types.h"

class Game {
public:
	GameState* CurrentState;

	bool ExecuteMove(uint32_t move);
	void ReverseMove();

	void NextTurn();
	void PreviousTurn();

	Game();
	explicit Game(const std::string& fen);
};
