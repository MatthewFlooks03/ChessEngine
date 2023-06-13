#pragma once
#include <iostream>
#include <iomanip>

#define U64 uint64_t
#define U8 uint8_t

namespace types {
	struct Magic {
		U64 magic = 0;
		U64 mask = 0;
		U8 indexBits = 0;
		U8 offset = 0;
	};


	const U64 FILE_A = 0x0101010101010101;
	const U64 FILE_H = 0x8080808080808080;
	const U64 RANK_1 = 0x00000000000000ff;
	const U64 RANK_8 = 0xff00000000000000;

	constexpr U64 north(U64 bitboard) { return (bitboard & ~RANK_8) << 8; } // Shift the bitboard north 
	constexpr U64 south(U64 bitboard) { return (bitboard & ~RANK_1) >> 8; } // Shift the bitboard south
	constexpr U64 east(U64 bitboard) { return (bitboard & ~FILE_H) << 1; } // Shift the bitboard east
	constexpr U64 west(U64 bitboard) { return (bitboard & ~FILE_A) >> 1; } // Shift the bitboard west
	constexpr U64 north_east(U64 bitboard) { return north(east(bitboard)); } // Shift the bitboard north east
	constexpr U64 north_west(U64 bitboard) { return north(west(bitboard)); } // Shift the bitboard north west
	constexpr U64 south_east(U64 bitboard) { return south(east(bitboard)); } // Shift the bitboard south west
	constexpr U64 south_west(U64 bitboard) { return south(west(bitboard)); } // Shift the bitboard south west
	constexpr U64 int_to_bitboard(int pos) { return (U64)0x1 << pos; } // Convert an integer to a bitboard

	extern void PrintBitboardArray(U64 bitboard[], int length = 64);
	extern void PrintIndexArray(U8 index[], int length = 64);
	extern void PrintBitboard(U64 bitboard);
};
