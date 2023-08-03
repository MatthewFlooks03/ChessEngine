#include "gamestate.h"
#include "tables.h"
#include "types.h"
#include "movegeneration.h"
#include "testing.h"
#include <bitset>

int main()
{
	Tables::Init();

	//Correct up to depth 6, from starting position


	//GameState gameState("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1 ");

	//GameState gameState("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1");
	//GameState gameState("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/2KR3R b kq - 1 1");
	//GameState gameState("r3k2r/p1pp1pb1/bn2pnp1/2qPN3/1p2P3/2N2Q1p/PPPBBPPP/2KR3R w kq - 2 2");
	//GameState gameState("r3k2r/p1pp1pb1/bn2pQp1/2qPN3/1p2P3/2N4p/PPPBBPPP/2KR3R b kq - 0 2");
	GameState gameState("r3k2r/p1pp1pb1/bn2pQp1/2q5/1p2P3/P1N4p/PPPBBP2/2KR4 b kq - 0 2");
		
	
	
	/*
	uint32_t move = MoveGeneration::GetAllPseudoMoves(gameState)[2];
	for (uint32_t move : MoveGeneration::GetAllPseudoMoves(gameState))
	{
		Types::PrintMove(move);
		std::cout << std::bitset<4>(gameState.CastlingRights) << std::endl;
		Types::PrintFullBoard(gameState);

		if (gameState.ExecuteMove(move))
		{
			Types::PrintFullBoard(gameState);
			std::cout << "PASSED";

			gameState.ReverseMove(move);
		}
		Types::PrintFullBoard(gameState);
	}
	*/
	

	Testing::Divide(1, gameState);


	/*
	std::vector<uint32_t> moves = MoveGeneration::GetAllPseudoMoves(gameState);

	std::cout << "Moves: " << moves.size() << std::endl;
	for(auto iterator = moves.begin(); iterator != moves.end(); ++iterator)
	{
		Types::PrintMove(*iterator);
	}
	*/

	/*
	GameState gameState("8/8/8/8/3b4/8/8/8 w - - 0 1");
	Types::PrintBitboard(MoveGeneration::GetAllAttacks(gameState, Types::Black));
	Types::PrintFullBoard(gameState);
	*/

	return 0;
}
