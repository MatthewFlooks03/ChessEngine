#pragma once
#include "types.h"

class PreGeneration
{
public:
	static void Generate();

private:
	static void GetKing(uint64_t moves[64]);
	static void GetKnight(uint64_t moves[64]);
	static void GetWhitePawnAttacks(uint64_t moves[64]);
	static void GetBlackPawnAttacks(uint64_t moves[64]);
	static void GetWhitePawnSinglePush(uint64_t moves[64]);
	static void GetBlackPawnSinglePush(uint64_t moves[64]);
	static void GetWhitePawnDoublePush(uint64_t moves[64]);
	static void GetBlackPawnDoublePush(uint64_t moves[64]);

	static void GetRookMasks(uint64_t masks[64]);
	static void GetBishopMasks(uint64_t masks[64]);

	static void PrintBitboardArray(uint64_t bitboard[], int length = 64);
	static void PrintIndexArray(uint8_t index[], int length = 64);

	static void GenerateRookMagics(uint64_t magics[64], uint8_t indexBits[64]);
	static void GenerateBishopMagics(uint64_t magics[64], uint8_t indexBits[64]);

	static void GenerateMagics(uint64_t magics[64], uint8_t indexBits[64], uint64_t masks[64], bool rook);
	static bool TryMakeTable(const Types::Magic& magic);

	static uint64_t GetRookSlidingMoves(int square, uint64_t blockers);
	static uint64_t GetBishopSlidingMoves(int square, uint64_t blockers);
};
