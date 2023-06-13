#pragma once
#include <map>
#include <random>
#include <iostream>

#define U64 uint64_t

struct Magic {
	U64 mask;
	U64 magic;
	uint8_t indexBits;
	U64 tableOffset;
};

// Bitboard Constants

// Jumping Pieces
extern const U64 KING_ATTACKS[64];
extern const U64 KNIGHT_ATTACKS[64];
extern const U64 WHITE_PAWN_ATTACKS[64];
extern const U64 BLACK_PAWN_ATTACKS[64];

// Sliding Pieces
//Masks
extern const U64 ROOK_MAGIC_MASKS[64];
extern const U64 BISHOP_MAGIC_MASKS[64];

//Magics
extern void initRookMagics();
extern void initBishopMagics();

extern U64 getRookSlidingMoves(int square, U64 blockers);
extern U64 magicIndex(Magic magic, U64 blockers);
extern void getAllBlockers(U64* ALL_BLOCKERS, U64 AND_MASK);
extern bool tryMakeTable(Magic squareMagics, int square, std::map<U64, U64> moveTable, int bits);

