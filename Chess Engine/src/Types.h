#pragma once
#include <iostream>

namespace Types {
	constexpr uint64_t FILE_A = 0x0101010101010101;
	constexpr uint64_t FILE_H = 0x8080808080808080;
	constexpr uint64_t RANK_1 = 0x00000000000000ff;
	constexpr uint64_t RANK_8 = 0xff00000000000000;

	constexpr uint64_t North(const uint64_t bitboard) { return (bitboard & ~RANK_8) << 8; } // Shift the bitboard North 
	constexpr uint64_t South(const uint64_t bitboard) { return (bitboard & ~RANK_1) >> 8; } // Shift the bitboard South
	constexpr uint64_t East(const uint64_t bitboard) { return (bitboard & ~FILE_H) << 1; } // Shift the bitboard East
	constexpr uint64_t West(const uint64_t bitboard) { return (bitboard & ~FILE_A) >> 1; } // Shift the bitboard West
	constexpr uint64_t NorthEast(const uint64_t bitboard) { return North(East(bitboard)); } // Shift the bitboard North East
	constexpr uint64_t NorthWest(const uint64_t bitboard) { return North(West(bitboard)); } // Shift the bitboard North West
	constexpr uint64_t SouthEast(const uint64_t bitboard) { return South(East(bitboard)); } // Shift the bitboard South West
	constexpr uint64_t SouthWest(const uint64_t bitboard) { return South(West(bitboard)); } // Shift the bitboard South West
	constexpr uint64_t IntToBitboard(const int bitboard) { return 1ULL << bitboard; } // Convert an integer to a bitboard}

	extern uint64_t SetBit(uint64_t bitboard, uint8_t square);
	extern uint64_t ClearBit(uint64_t bitboard, uint8_t square);
	extern uint64_t GetBit(uint64_t bitboard, uint8_t square);
	extern uint64_t PopBit(uint64_t bitboard, uint8_t square);
	extern uint64_t CountBits(uint64_t bitboard);

	extern void PrintBitboard(uint64_t bitboard);
};
