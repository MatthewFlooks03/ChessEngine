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


	//Up to depth 6 then ?
	//Game game("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1 ");

	//Up to depth 4 then ?
	//Game game("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - ");

	//Up to depth 5 then ?
	//Game game("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - ");

	//Up to depth ? then ?
	//Game game("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1");

	//Up to depth 4 then ?
	//Game game("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8");

	//Game game("n1n5/PPPk4/8/8/8/8/4Kppp/5N1N b - - 0 1");
	
	if(0){ using namespace Types;
		bool failed = false;
		//PrintFullBoard(gameState);
		failed |= !(game.ExecuteMove(GenerateMove(White, King, None, E1, D1, 0, None, 0)));
		PrintFullBoard(*game.CurrentState);

		if (failed)
		{
			std::cout << "BAD EXECUTE" << std::endl;
			for (;;);
		}
	}


	const auto start = std::chrono::high_resolution_clock::now();
		
			//Types::PrintFullBoard(gameState);
	Testing::Divide(4, game);
			//Types::PrintFullBoard(gameState);

	const auto end = std::chrono::high_resolution_clock::now();

	std::cout << std::endl << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;

	return 0;
}
