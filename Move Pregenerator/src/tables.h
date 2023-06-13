#pragma once
#include "types.h"
using namespace Types;

class Tables
{
public:
	static void King(uint64_t moves[64]);
	static void Knight(uint64_t moves[64]);
	static void WhitePawnAttacks(uint64_t moves[64]);
	static void BlackPawnAttacks(uint64_t moves[64]);
	static void WhitePawnSingleMoves(uint64_t moves[64]);
	static void BlackPawnSingleMoves(uint64_t moves[64]);

	static void RookMasks(uint64_t masks[64]);
	static void BishopMasks(uint64_t masks[64]);
};
