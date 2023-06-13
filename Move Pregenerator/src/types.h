#pragma once
#include <iostream>
#include <iomanip>

namespace Types {

	struct Magic {
		uint64_t MagicNumber = 0;
		uint64_t Mask = 0;
		uint8_t IndexBits = 0;
		uint8_t Offset = 0;
	};


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
	constexpr uint64_t IntToBitboard(const int pos) { return 0x1ULL << pos; } // Convert an integer to a bitboard

	extern void PrintBitboardArray(uint64_t bitboard[], int length = 64);
	extern void PrintIndexArray(uint8_t index[], int length = 64);
	extern void PrintBitboard(uint64_t bitboard);
};
