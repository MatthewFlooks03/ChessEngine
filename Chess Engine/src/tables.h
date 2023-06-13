#pragma once
#include <unordered_map>
#include "types.h"
using namespace Types;

class Tables {
public:
	
	static constexpr uint64_t GetKingMoves(const uint8_t square) {return KING_ATTACKS[square];}
	static constexpr uint64_t GetKnightMoves(const uint8_t square) {return KNIGHT_ATTACKS[square];}
	static constexpr uint64_t GetWhitePawnAttacks(const uint8_t square) {return WHITE_PAWN_ATTACKS[square];}
	static constexpr uint64_t GetBlackPawnAttacks(const uint8_t square) {return BLACK_PAWN_ATTACKS[square];}
	uint64_t GetRookMoves(const uint8_t square, const uint64_t allPieces) const;
	uint64_t GetBishopMoves(const uint8_t square, const uint64_t allPieces) const;

	Tables();

private:
	class Magic {
	public:
		uint8_t Square;
		bool Rook;
		uint64_t Mask;
		uint64_t MagicNumber;
		uint8_t IndexBits;

		Magic(uint8_t square, bool rook);
	};

	void InitRookMoves() const;
	void InitBishopMoves() const;

	static const uint64_t KING_ATTACKS[64];
	static const uint64_t KNIGHT_ATTACKS[64];
	static const uint64_t WHITE_PAWN_ATTACKS[64];
	static const uint64_t BLACK_PAWN_ATTACKS[64];

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
	std::unordered_map<uint64_t, uint64_t>* RookMoves;
	std::unordered_map<uint64_t, uint64_t>* BishopMoves;

	static uint64_t MagicIndex(const Magic& magic, const uint64_t blockers);
	static uint64_t GetRookSlidingMoves(const int square, const uint64_t blockers);
	static uint64_t GetBishopSlidingMoves(const int square, const uint64_t blockers);
	static uint16_t GetAllBlockers(uint64_t allBlockers[4096], const uint64_t andMask);

	void MakeTable(const Magic& magic) const;
};
