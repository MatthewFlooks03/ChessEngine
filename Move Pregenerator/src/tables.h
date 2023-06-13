#pragma once
#include "types.h"
using namespace types;

class tables
{
public:
	static const void king(U64 moves[64]);
	static const void knight(U64 moves[64]);
	static const void whitePawnAttacks(U64 moves[64]);
	static const void blackPawnAttacks(U64 moves[64]);
	static const void whitePawnSingleMoves(U64 moves[64]);
	static const void blackPawnSingleMoves(U64 moves[64]);

	static const void rookMasks(U64 masks[64]);
	static const void bishopMasks(U64 masks[64]);
};
