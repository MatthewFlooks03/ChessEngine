#pragma once
#include <unordered_map>
#include "gamestate.h"
#include "types.h"

class Tables {
public:
	static uint64_t GetKingMoves(uint8_t square, const GameState& gameState, uint8_t color);
	static uint64_t GetKnightMoves(uint8_t square, const GameState& gameState, uint8_t color);
	static uint64_t GetBlackPawnMoves(uint8_t square, const GameState& gameState, uint8_t color);
	static uint64_t GetWhitePawnMoves(uint8_t square, const GameState& gameState, uint8_t color);
	static uint64_t GetRookMoves(uint8_t square, const GameState& gameState, uint8_t color);
	static uint64_t GetBishopMoves(uint8_t square, const GameState& gameState, uint8_t color);
	static uint64_t GetQueenMoves(uint8_t square, const GameState& gameState, uint8_t color);

	static void GetMagicTables(const uint8_t square, const bool rook, uint64_t* mask, uint64_t* magicNumber, uint8_t* indexBits);

	static void Init();

private:
	static void InitRookMoves();
	static void InitBishopMoves();

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
	static uint8_t GetRookIndexBits(uint8_t square);
	static uint8_t GetBishopIndexBits(uint8_t square);

	// Moves Storage
	static std::unordered_map<uint64_t, uint64_t>** RookMoves;
	static std::unordered_map<uint64_t, uint64_t>** BishopMoves;

	static void MakeTable(const Types::Magic& magic);

	static uint64_t MagicIndex(const Types::Magic& magic, const uint64_t blockers);
	static uint64_t GetRookSlidingMoves(const int square, const uint64_t blockers);
	static uint64_t GetBishopSlidingMoves(const int square, const uint64_t blockers);
	static uint16_t GetAllBlockers(uint64_t allBlockers[4096], const uint64_t andMask);
};
