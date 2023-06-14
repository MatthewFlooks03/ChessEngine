#pragma once
#include <unordered_map>
#include "types.h"
using namespace Types;

class Tables {
public:
	static constexpr uint64_t GetKingMoves(const uint8_t square) {return KING_ATTACKS[square];}
	static constexpr uint64_t GetKnightMoves(const uint8_t square) {return KNIGHT_ATTACKS[square];}
	static uint64_t GetBlackPawnMoves(const uint8_t square, const uint64_t allPieces);
	static uint64_t GetWhitePawnMoves(const uint8_t square, const uint64_t allPieces);
	uint64_t GetRookMoves(const uint8_t square, const uint64_t allPieces) const;
	uint64_t GetBishopMoves(const uint8_t square, const uint64_t allPieces) const;

	static bool RookMagicTesting();
	static bool BishopMagicTesting();

	Tables();

	static void GetMagicTables(const uint8_t square, const bool rook, uint64_t* mask, uint64_t* magicNumber, uint8_t* indexBits);
	static uint64_t MagicIndex(const Magic& magic, const uint64_t blockers);
	static uint64_t GetRookSlidingMoves(const int square, const uint64_t blockers);
	static uint64_t GetBishopSlidingMoves(const int square, const uint64_t blockers);
	static uint16_t GetAllBlockers(uint64_t allBlockers[4096], const uint64_t andMask);

private:
	void InitRookMoves() const;
	void InitBishopMoves() const;

	static const uint64_t KING_ATTACKS[64];
	static const uint64_t KNIGHT_ATTACKS[64];
	static const uint64_t WHITE_PAWN_ATTACKS[64];
	static const uint64_t BLACK_PAWN_ATTACKS[64];
	static const uint64_t BLACK_PAWN_SINGLE_PUSH[64];
	static const uint64_t WHITE_PAWN_SINGLE_PUSH[64];
	static const uint64_t BLACK_PAWN_DOUBLE_PUSH[64];
	static const uint64_t WHITE_PAWN_DOUBLE_PUSH[64];

	// Masks
	static const uint64_t ROOK_MAGIC_MASKS[64];
	static const uint64_t BISHOP_MAGIC_MASKS[64];

	// Magics
	static const uint64_t ROOK_MAGICS[64];
	static const uint64_t BISHOP_MAGICS[64];

	// Index Bits
	static const uint8_t ROOK_INDEX_BITS[64];
	static const uint8_t BISHOP_INDEX_BITS[64];

	// Moves Storage
	std::unordered_map<uint64_t, uint64_t>** RookMoves;
	std::unordered_map<uint64_t, uint64_t>** BishopMoves;

	void MakeTable(const Magic& magic) const;
};
