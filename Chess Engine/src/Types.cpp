#include "types.h"
#include "tables.h"

namespace Types {
	uint64_t SetBit(const uint64_t bitboard, const uint8_t square) { return bitboard | (1ULL << square); } // Set the bit at the Square
	uint64_t ClearBit(const uint64_t bitboard, const uint8_t square) { return bitboard & ~(1ULL << square); } // Clear the bit at the Square
	uint64_t GetBit(const uint64_t bitboard, const uint8_t square) { return bitboard & (1ULL << square); } // Get the bit at the Square
	uint64_t PopBit(const uint64_t bitboard, const uint8_t square) { return GetBit(bitboard, square) | ClearBit(bitboard, square); } // Pop the bit at the Square
	uint64_t CountBits(const uint64_t bitboard) { return __popcnt64(bitboard); } // Count the number of bits in the bitboard

	void PrintBitboard(const uint64_t bitboard) {
		for (int y = 7; y >= 0; y--) {
			for (int x = 0; x < 8; x++)
			{
				std::cout << ((bitboard >> (y * 8 + x)) & 1) << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
}
