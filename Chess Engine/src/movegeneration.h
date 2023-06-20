#pragma once
#include "types.h"
#include "gamestate.h"
#include <list>

class MoveGeneration
{
public:
	static std::list<uint32_t> GenerateAllPseudoMoves(const GameState& gameState);

private:
	static void GeneratePseudoMoves(const GameState& gameState, uint8_t piece, std::list<uint32_t>* moves);
};
