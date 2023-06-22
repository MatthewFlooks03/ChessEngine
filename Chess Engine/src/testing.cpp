#include "testing.h"
#include "movegeneration.h"

uint64_t Testing::Perft(const int depth, GameState& gameState )
{
	if(depth == 0)
	{
		return 1;
	}

	uint64_t nodes = 0;

	std::vector<uint32_t> moves = MoveGeneration::GetAllPseudoMoves(gameState);

	for(auto iterator = moves.begin(); iterator != moves.end(); ++iterator)
	{
		if (gameState.ExecuteMove(*iterator))
		{
			nodes += Perft(depth - 1, gameState);
		}
		gameState.ReverseMove(*iterator);
	}
	return nodes;
}
