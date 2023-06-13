#pragma once
#include "types.h"
using namespace Types;

class BitBoard {
public:
	uint64_t WhiteKing;
	uint64_t WhiteQueen;
	uint64_t WhiteRook;
	uint64_t WhiteBishop;
	uint64_t WhiteKnight;
	uint64_t WhitePawn;

	uint64_t BlackKing;
	uint64_t BlackQueen;
	uint64_t BlackRook;
	uint64_t BlackBishop;
	uint64_t BlackKnight;
	uint64_t BlackPawn;

	uint64_t WhitePieces;
	uint64_t BlackPieces;
	uint64_t AllPieces;
};
