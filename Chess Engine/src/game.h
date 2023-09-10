#pragma once
#include "types.h"

class Game {
public:
	GameState* CurrentState;

	bool ExecuteMove(uint32_t move);
	void ReverseMove();

	Game();
	explicit Game(const std::string& fen);
	~Game();

	std::string GetFen() const;

private:
	uint32_t HalfMoveCount;
	uint32_t FullMoveCount;
};
