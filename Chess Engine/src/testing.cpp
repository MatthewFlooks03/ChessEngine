#include "testing.h"
#include "movegeneration.h"

uint64_t Testing::Perft(const int depth, GameState& gameState )
{
	if(depth == 0)
	{
		return 1;
	}
	uint64_t nodes = 0;

	const std::vector<uint32_t> moves = MoveGeneration::GetAllPseudoMoves(gameState);
	for (unsigned const int& move : moves)
	{
		GameState initialState = gameState;
		GameState movedState;

		if (gameState.ExecuteMove(move))
		{
			const uint64_t prevNodes = Perft(depth - 1, gameState);
			nodes += prevNodes;
			gameState.ReverseMove();

			/*
			for(int i = 0; i < 5 - depth; i++)
			{
				std::cout << "\t";
			}
			Types::PrintMoveSquare(move);
			std::cout << ": " << prevNodes << std::endl;
			*/
			/*
			if((gameState != initialState))
			{
				std::cout << "BAD REVERSE" << std::endl;
				Types::PrintMove(move);

				initialState.GetDifference(gameState);

			//Types::PrintFullBoard(initialState);
			//Types::PrintFullBoard(movedState);
			//Types::PrintFullBoard(gameState);
			Types::PrintBitboard(initialState.EnPassantSquare);
			Types::PrintBitboard(gameState.EnPassantSquare);
			}
			*/

		}
				
	}
	return nodes;
}

void Testing::Divide(const int depth, GameState& gameState)
{
	const std::vector<uint32_t> moves = MoveGeneration::GetAllPseudoMoves(gameState);

	uint64_t allNodes = 0;

	for (unsigned const int& move : moves)
	{
		//std::cout << "Move: ";
		//Types::PrintFullBoard(gameState);
		if (gameState.ExecuteMove(move))
		{
			const uint64_t prevNodes = Perft(depth - 1, gameState);
			allNodes += prevNodes;

			Types::PrintMoveSquare(move);
			std::cout << ": " << prevNodes << std::endl;

			gameState.ReverseMove();

			//std::cout << "Reversed:";
			//Types::PrintFullBoard(gameState);
			//std::cout << std::endl << std::endl;
		}
	}
	std::cout << "Nodes: " << allNodes << std::endl;
}
