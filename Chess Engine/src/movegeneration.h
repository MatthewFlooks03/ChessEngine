#pragma once
#include "types.h"
#include "gamestate.h"
#include <vector>

class MoveGeneration
{
public:
	static std::vector<uint32_t> GetAllPseudoMoves(const GameState& gameState);
	static uint64_t GetAllAttacks(const GameState& gameState, uint8_t color);

//private:
	static void GetPseudoMoves(const GameState& gameState, uint8_t pieceMoved, std::vector<uint32_t>* moves);

	static uint64_t GetQueenAttacks(uint64_t bitboard, const GameState& gameState, uint8_t color);
	static uint64_t GetKingAttacks(uint64_t bitboard, uint8_t color);
	static uint64_t GetRookAttacks(uint64_t bitboard, const GameState& gameState, uint8_t color);
	static uint64_t GetBishopAttacks(uint64_t bitboard, const GameState& gameState, uint8_t color);
	static uint64_t GetKnightAttacks(uint64_t bitboard, uint8_t color);
	static uint64_t GetPawnAttacks(uint64_t bitboard, uint8_t color);
};
