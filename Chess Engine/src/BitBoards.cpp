#include "pch.h"
#include "BitBoards.h"
#include "Types.cpp"

#define U64 uint64_t

void BitBoards::GenerateBitBoards() {
	// Generate bitboards for each piece
	// White pieces
	WhiteKing = 0x0000000000000010;
	WhiteQueen = 0x0000000000000008;
	WhiteRook = 0x0000000000000081;
	WhiteBishop = 0x0000000000000024;
	WhiteKnight = 0x0000000000000042;
	WhitePawn = 0x000000000000FF00;
	// Black pieces
	BlackKing = 0x1000000000000000;
	BlackQueen = 0x0800000000000000;
	BlackRook = 0x8100000000000000;
	BlackBishop = 0x2400000000000000;
	BlackKnight = 0x4200000000000000;
	BlackPawn = 0x00FF000000000000;
	// All pieces
	WhitePieces = WhiteKing | WhiteQueen | WhiteRook | WhiteBishop | WhiteKnight | WhitePawn;
	BlackPieces = BlackKing | BlackQueen | BlackRook | BlackBishop | BlackKnight | BlackPawn;
}

void BitBoards::DrawBitBoard(U64 bitboard) {
	// Draw a bitboard to the console
	std::cout << std::endl;
	for (int i = 0; i < 64; i++) {
		if (i % 8 == 0) {
			std::cout << std::endl;
		}
		std::cout << ((bitboard >> i) & 1);
	}
	std::cout << std::endl;
}
