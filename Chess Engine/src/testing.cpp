#include "testing.h"
#include "movegeneration.h"

uint64_t Testing::Perft(const int depth, Game& game )
{
	const GameState* gameState = game.CurrentState;

	if(depth == 0)
	{
		return 1;
	}
	uint64_t nodes = 0;

	const std::vector<uint32_t> moves = MoveGeneration::GetAllPseudoMoves(*gameState);
	for (unsigned const int& move : moves)
	{
		GameState initialState = *gameState;

		if (game.ExecuteMove(move))
		{
			const uint64_t prevNodes = Perft(depth - 1, game);

			const GameState movedState = *gameState;

			nodes += prevNodes;
			game.ReverseMove();

			/*
			for(int i = 0; i < 5 - depth; i++)
			{
				std::cout << "\t";
			}
			Types::PrintMoveSquare(move);
			std::cout << ": " << prevNodes << std::endl;
			*/
			if((*gameState != initialState))
			{
				std::cout << "BAD REVERSE" << std::endl;
				Types::PrintMove(move);

				initialState.GetDifference(*gameState);

				Types::PrintFullBoard(initialState);
				Types::PrintFullBoard(movedState);
				Types::PrintFullBoard(*gameState);
				for (;;);
			}

		}
				
	}
	return nodes;
}

void Testing::Divide(const int depth, Game& game)
{
	const GameState* gameState = game.CurrentState;

	const std::vector<uint32_t> moves = MoveGeneration::GetAllPseudoMoves(*gameState);

	uint64_t allNodes = 0;
	int count = 0;

	for (unsigned const int& move : moves)
	{
		if (game.ExecuteMove(move))
		{
			const uint64_t prevNodes = Perft(depth - 1, game);
			allNodes += prevNodes;

			Types::PrintMoveSquare(move);
			std::cout << ": " << prevNodes << std::endl;

			//Types::PrintFullBoard(gameState);

			game.ReverseMove();

			std::cout << "Move: ";
			Types::PrintMove(move); std::cout << std::endl;
			//std::cout << "Reversed:";
			//Types::PrintFullBoard(gameState);
			//std::cout << std::endl << std::endl;
			count++;
		}
	}
	std::cout << "Moves: " << count << std::endl;
	std::cout << "Nodes: " << allNodes << std::endl;
}
