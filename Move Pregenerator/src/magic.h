#pragma once
#include <random>
#include "types.h"
#include "tables.h"
#include <limits.h>
using namespace types;

class magic
{
public:
	static void generateRookMagics(U64 magics[64], U8 indexBits[64]);
	static void generateBishopMagics(U64 magics[64], U8 indexBits[64]);

	static void generateMagics(U64 magics[64], U8 indexBits[64], U64 masks[64], bool rook);
	static bool tryMakeTable(Magic magic, int square, bool rook);
	static int getAllBlockers(U64 allBlockers[4096], U64 andMask);
	static U64 magicIndex(Magic magic, U64 blockers);


	static U64 getRookSlidingMoves(int square, U64 blockers);
	static U64 getBishopSlidingMoves(int square, U64 blockers);
};
