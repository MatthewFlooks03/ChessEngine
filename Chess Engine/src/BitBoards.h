#pragma once
#include "Types.h"

class BitBoards {
public:
	void GenerateBitBoards();
	void DrawBitBoard(U64 bitboard);

	U64 WhiteKing;
	U64 WhiteQueen;
	U64 WhiteRook;
	U64 WhiteBishop;
	U64 WhiteKnight;
	U64 WhitePawn;

	U64 BlackKing;
	U64 BlackQueen;
	U64 BlackRook;
	U64 BlackBishop;
	U64 BlackKnight;
	U64 BlackPawn;

	U64 WhitePieces;
	U64 BlackPieces;
	U64 AllPieces;
};
