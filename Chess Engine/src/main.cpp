#include "gamestate.h"
#include "tables.h"
#include "types.h"
#include "movegeneration.h"
#include "testing.h"

int main()
{
	Tables::Init();

	GameState gameState("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1 ");

	std::cout << Testing::Perft(3, gameState) << std::endl;

	/*
	std::vector<uint32_t> moves = MoveGeneration::GetAllPseudoMoves(gameState);

	std::cout << "Moves: " << moves.size() << std::endl;
	for(auto iterator = moves.begin(); iterator != moves.end(); ++iterator)
	{
		Types::PrintMove(*iterator);
	}
	*/

	return 0;
}
