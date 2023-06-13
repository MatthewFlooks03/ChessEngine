#pragma once

#include "pch.h"
#include <iostream>




#define U64 uint64_t

// Board Coords
//TODO: Add board coords
extern const U64 FILE_A;
extern const U64 FILE_H;
extern const U64 RANK_1;
extern const U64 RANK_8;

//extern const uint8_t N_SQUARES = 64;


#define set_bit(bitboard, square) bitboard |= (1U64 << square); // Set the bit at the square
#define clear_bit(bitboard, square) bitboard &= ~(1U64 << square); // Clear the bit at the square
#define get_bit(bitboard, square) (bitboard & (1U64 << square)); // Get the bit at the square
#define pop_bit(bitboard, square) {get_bit(bitboard, square); clear_bit(bitboard, square);} // Pop the bit at the square

#define count_bits(bitboard) __popcnt64(bitboard) // Count the number of bits in the bitboard

constexpr U64 north(U64 bitboard) {return bitboard & ~RANK_8 << 8;} // Shift the bitboard north 
constexpr U64 south(U64 bitboard) {return bitboard & ~RANK_1 >> 8;} // Shift the bitboard south
constexpr U64 east(U64 bitboard) {return bitboard & ~FILE_A << 1;} // Shift the bitboard east
constexpr U64 west(U64 bitboard) {return bitboard & ~FILE_H >> 1;} // Shift the bitboard west
