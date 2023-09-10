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


	Game game("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1 ");
	
	const auto now = std::chrono::high_resolution_clock::now();
	auto out = Testing::Speed(6, game, now, 10000);
	std::cout << out << std::endl;

	/*
	const auto start = std::chrono::high_resolution_clock::now();
		
	Testing::Divide(4, game);

	const auto end = std::chrono::high_resolution_clock::now();

	std::cout << std::endl << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;
	*/

	

	return 0;
}
