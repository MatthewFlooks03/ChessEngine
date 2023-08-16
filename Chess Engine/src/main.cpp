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
	GameState gameState("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1 ");

	//Correct up to depth 3
	//GameState gameState("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - ");

	//Correct up to depth 5
	//GameState gameState("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - ");

	//GameState gameState("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1");
	//GameState gameState("r3k2r/Pppp1ppp/1b3nbN/nPB5/B1P1P3/q4N2/Pp1P2PP/R2Q1RK1 b kq - 1 1");
	//GameState gameState("4k2r/rppp1ppp/1b3nbN/nPB5/B1P1P3/q4N2/Pp1P2PP/R2Q1RK1 w k - 0 2");
	//GameState gameState("4k2r/rppp1ppp/1b3nbN/nPB5/B1P1P3/q4N2/Pp1P2PP/1R1Q1RK1 b k - 1 2");
		
			//Types::PrintFullBoard(gameState);
	Testing::Divide(4, gameState);
			//Types::PrintFullBoard(gameState);


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
