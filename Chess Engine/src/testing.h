#pragma once
#include <chrono>

#include "game.h"
#include "types.h"


class Testing
{
public:
	static uint64_t Perft(int depth, Game& game);
	static void Divide(int depth, Game& game);
	static uint64_t Speed(int depth, Game& game, std::chrono::time_point<std::chrono::steady_clock> start, long long testTime);
};

