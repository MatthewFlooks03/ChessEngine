#include "types.h"
#include "tables.h"

namespace Types {

	/* Methods */
	uint64_t SetBit(const uint64_t bitboard, const uint8_t square) { return bitboard | (1ULL << square); } // Set the bit at the Square
	uint64_t ClearBit(const uint64_t bitboard, const uint8_t square) { return bitboard & ~(1ULL << square); } // Clear the bit at the Square
	uint64_t GetBit(const uint64_t bitboard, const uint8_t square) { return bitboard & (1ULL << square); } // Get the bit at the Square
	uint64_t PopBit(const uint64_t bitboard, const uint8_t square) { return GetBit(bitboard, square) | ClearBit(bitboard, square); } // Pop the bit at the Square
	uint64_t CountBits(const uint64_t bitboard) { return __popcnt64(bitboard); } // Count the number of bits in the bitboard
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

	std::vector<uint8_t> SerialiseBitboard(uint64_t bitboard)
	{
		std::vector<uint8_t> squares;

		if(bitboard) do
		{
			const uint8_t idx = BitScanForward(bitboard);
			squares.push_back(idx);
		} while(bitboard &= bitboard - 1);
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
	void PrintMove(const uint32_t move)
	{
		const uint8_t color = (move >> 31) & 0b1;
		const uint8_t pieceMoved = (move >> 28) & 0b111;
		const uint8_t pieceCaptured = (move >> 25) & 0b111;
		const uint8_t initialPosition = (move >> 19) & 0b111111;
		const uint8_t finalPosition = (move >> 13) & 0b111111;
		const uint8_t enPassant = (move >> 7) & 0b111111;
		const uint8_t promotion = (move >> 4) & 0b111;
		const uint8_t castling = move & 0b1111;

		const std::string colors[2] = { "White", "Black"};
		const std::string pieces[8] = { "King", "Queen", "Rook", "Bishop", "Knight", "Pawn", "EnPassant", "None"};
		const std::string castle[9] = { "", "BlackQueenSide", "BlackKingSide", "", "WhiteQueenSide", "", "", "", "WhiteKingSide"};
		const std::string squares[64] = {
			"A1", "B1", "C1", "D1", "E1", "F1", "G1", "H1",
			"A2", "B2", "C2", "D2", "E2", "F2", "G2", "H2",
			"A3", "B3", "C3", "D3", "E3", "F3", "G3", "H3",
			"A4", "B4", "C4", "D4", "E4", "F4", "G4", "H4",
			"A5", "B5", "C5", "D5", "E5", "F5", "G5", "H5",
			"A6", "B6", "C6", "D6", "E6", "F6", "G6", "H6",
			"A7", "B7", "C7", "D7", "E7", "F7", "G7", "H7",
			"A8", "B8", "C8", "D8", "E8", "F8", "G8", "H8"
		};

		std::cout << colors[color] << ", "
			<< pieces[pieceMoved]<< ", "
			<< pieces[pieceCaptured] << ", "
			<< squares[initialPosition] << ", "
			<< squares[finalPosition] << ", "
			<< (enPassant == 0 ? "-" : squares[enPassant]) << ", "
			<< pieces[promotion] << ", "
			<< castle[castling] << std::endl;
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
