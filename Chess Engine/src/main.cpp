#include "gamestate.h"
#include "tables.h"
#include "types.h"
#include "movegeneration.h"
#include "testing.h"
#include <bitset>
#include <chrono>

#include "game.h"

int main()
{
	Tables::Init();

	//Up to depth 5 then wrong
	//GameState gameState("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1 ");

	//Up to depth 4 then wrong
	//GameState gameState("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - ");

	//Up to depth 6
	//GameState gameState("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - ");

	//Up to depth 5
	//GameState gameState("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1");

	//Up to depth 4 then wrong
	//GameState gameState("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8");

	Game game("4k3/8/8/8/8/8/8/4K2R w K - 0 1");
	
	if(1){ using namespace Types;
		bool failed = false;
		//PrintFullBoard(gameState);
		failed |= !(game.ExecuteMove(GenerateMove(White, King, None, E1, F1, 0, None, 0)));
		failed |= !(game.ExecuteMove(GenerateMove(Black, King, None, E8, D7, 0, None, 0)));
		failed |= !(game.ExecuteMove(GenerateMove(White, King, None, F1, E1, 0, None, 0)));
		failed |= !(game.ExecuteMove(GenerateMove(Black, King, None, D7, C6, 0, None, 0)));
		PrintFullBoard(*game.CurrentState);

		if (failed)
		{
			std::cout << "BAD EXECUTE" << std::endl;
			for (;;);
		}
	}


	const auto start = std::chrono::high_resolution_clock::now();
		
			//Types::PrintFullBoard(gameState);
	Testing::Divide(1, game);
			//Types::PrintFullBoard(gameState);

	const auto end = std::chrono::high_resolution_clock::now();

	std::cout << std::endl << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;

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
