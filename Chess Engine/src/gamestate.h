#pragma once
#include "types.h"

class GameState {
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

	uint64_t EnPassantSquare;

	uint8_t CastlingRights; // NA NA NA NA WK WQ BK BQ 

	uint8_t SideToMove; // 0 - white, 1 - black

	constexpr uint64_t WhitePieces() const { return WhiteKing | WhiteQueen | WhiteRook | WhiteBishop | WhiteKnight | WhitePawn; } 
	constexpr uint64_t BlackPieces() const { return BlackKing | BlackQueen | BlackRook | BlackBishop | BlackKnight | BlackPawn; }
	constexpr uint64_t AllPieces() const { return WhitePieces() | BlackPieces(); }

	GameState();

	uint64_t operator[](uint8_t bitboard) const;
	uint64_t& operator[](uint8_t bitboard);

	/*
		MSB
	 * unused (9) 
	 * piece color (1)
	 * piece to move (3) (NM-0, K-1, Q-2, R-3, B-4, K-5, P-6)
	 * piece to capture (3) (NC-0, K-1, Q-2, R-3, B-4, K-5, P-6, E-7)
	 * castling (4) (NC-0, WK WQ BK BQ)
	 * initial pos (6) (0-63)
	 * final pos (6) (0-63)
		LSB
	 */
	uint8_t GetPiece(uint8_t square, uint8_t color) const;
	bool ExecuteMove(uint32_t move);
	void ReverseMove(uint32_t move);
};
