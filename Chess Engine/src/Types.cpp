#include "types.h"
#include "tables.h"

namespace Types {

	/* Methods */
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

	uint8_t PopCount(uint64_t bitboard)
	{
		uint8_t count = 0;
		while (bitboard > 0)
		{
			if((bitboard & 1) == 1)
			{
				count++;
			}
			bitboard >>= 1;
		}
		return count;
	}

	std::list<uint8_t> SerialiseBitboard(uint64_t bitboard)
	{
		std::list<uint8_t> squares;

		if(bitboard) do
		{
			const uint8_t idx = BitScanForward(bitboard);
			squares.push_back(idx);
			bitboard ^= 1ULL << idx;
		} while(bitboard & bitboard - 1);
		return squares;
	}

	uint8_t BitScanForward(const uint64_t bitboard)
	{
		const uint8_t index64[64] = {
					0, 47,  1, 56, 48, 27,  2, 60,
					57, 49, 41, 37, 28, 16,  3, 61,
					54, 58, 35, 52, 50, 42, 21, 44,
					38, 32, 29, 23, 17, 11,  4, 62,
					46, 55, 26, 59, 40, 36, 15, 53,
					34, 51, 20, 43, 31, 22, 10, 45,
					25, 39, 14, 33, 19, 30,  9, 24,
					13, 18,  8, 12,  7,  6,  5, 63
				};
		const uint64_t debruijn64 = 0x03f79d71b4cb0a89ULL;
		return index64[((bitboard ^ (bitboard-1)) * debruijn64 >> 58)];
	}

	/* Magic */
	Magic::Magic(const uint8_t square, const bool rook)
	{
		this->Square = square;
		this->Rook = rook;
		this->Mask = 0;
		this->MagicNumber = 0;
		this->IndexBits = 0;
		Tables::GetMagicTables(square, rook, &Mask, &MagicNumber, &IndexBits);
	}

	Magic::Magic()
	{
		this->Square = 0;
		this->Rook = false;
		this->Mask = 0;
		this->MagicNumber = 0;
		this->IndexBits = 0;
	}

}
