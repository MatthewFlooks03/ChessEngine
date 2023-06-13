#pragma once
#include "types.h"
#include "Tables.h"
using namespace Types;

class magic
{
public:
	static void GenerateRookMagics(uint64_t magics[64], uint8_t indexBits[64]);
	static void GenerateBishopMagics(uint64_t magics[64], uint8_t indexBits[64]);

	static void GenerateMagics(uint64_t magics[64], uint8_t indexBits[64], uint64_t masks[64], bool rook);
	static bool TryMakeTable(const Magic& magic, int square, bool rook);
	static int GetAllBlockers(uint64_t allBlockers[4096], uint64_t andMask);
	static uint64_t MagicIndex(const Magic& magic, uint64_t blockers);


	static uint64_t GetRookSlidingMoves(int square, uint64_t blockers);
	static uint64_t GetBishopSlidingMoves(int square, uint64_t blockers);
};
