#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>

class GameState;

namespace Types {
	/* Enums */
	enum Color: uint8_t
	{
		White = 0,
		Black = 1
	};

	enum Square: uint8_t
	{
		A1, B1, C1, D1, E1, F1, G1, H1,
		A2, B2, C2, D2, E2, F2, G2, H2,
		A3, B3, C3, D3, E3, F3, G3, H3,
		A4, B4, C4, D4, E4, F4, G4, H4,
		A5, B5, C5, D5, E5, F5, G5, H5,
		A6, B6, C6, D6, E6, F6, G6, H6,
		A7, B7, C7, D7, E7, F7, G7, H7,
		A8, B8, C8, D8, E8, F8, G8, H8
	};

	enum Piece: uint8_t
	{
		King,		//0
		Queen,		//1
		Rook,		//2
		Bishop,		//3	
		Knight,		//4
		Pawn,		//5
		EnPassant,	//6
		None		//7
	};

	enum CastlingRights: uint8_t
	{
		WhiteKingSide = 8,
		WhiteQueenSide = 4,
		BlackKingSide = 2,
		BlackQueenSide = 1
	};

	/* Move within uint32_t
		MSB
	 * Color (1)
	 * Piece Moved (3)
	 * Piece Captured (3)
	 * Initial Position (6)
	 * Final Position (6)
	 * En Passant (6)
	 * Promotion (3)
	 * Castling (4)
		LSB
	 */

	/* Constants */
	constexpr uint64_t FILE_A = 0x0101010101010101;
	constexpr uint64_t FILE_H = 0x8080808080808080;
	constexpr uint64_t RANK_1 = 0x00000000000000ff;
	constexpr uint64_t RANK_8 = 0xff00000000000000;

	/* Methods */
	constexpr uint64_t North(const uint64_t bitboard) { return (bitboard & ~RANK_8) << 8; } // Shift the bitboard North 
	constexpr uint64_t South(const uint64_t bitboard) { return (bitboard & ~RANK_1) >> 8; } // Shift the bitboard South
	constexpr uint64_t East(const uint64_t bitboard) { return (bitboard & ~FILE_H) << 1; } // Shift the bitboard East
	constexpr uint64_t West(const uint64_t bitboard) { return (bitboard & ~FILE_A) >> 1; } // Shift the bitboard West
	constexpr uint64_t NorthEast(const uint64_t bitboard) { return North(East(bitboard)); } // Shift the bitboard North East
	constexpr uint64_t NorthWest(const uint64_t bitboard) { return North(West(bitboard)); } // Shift the bitboard North West
	constexpr uint64_t SouthEast(const uint64_t bitboard) { return South(East(bitboard)); } // Shift the bitboard South West
	constexpr uint64_t SouthWest(const uint64_t bitboard) { return South(West(bitboard)); } // Shift the bitboard South West

	constexpr uint64_t IntToBitboard(const int square) {  return 1ULL << square;} // Convert an integer to a bitboard}
	constexpr uint64_t GetFile(const int square) { return (square % 8); } // Get the file of a square
	constexpr uint64_t GetRank(const int square) { return (square / 8); } // Get the rank of a square

	constexpr uint32_t GenerateMove(const uint8_t color, const uint8_t piece, const uint8_t captured, const uint8_t initial, const uint8_t final, const uint8_t enPassant, const uint8_t promotion, const uint8_t castling) { return (color << 31) | (piece << 28) | (captured << 25) | (initial << 19) | (final << 13) | (enPassant << 7) | (promotion << 4) | castling; }

	extern uint64_t SetBit(uint64_t bitboard, uint8_t square);
	extern uint64_t ClearBit(uint64_t bitboard, uint8_t square);
	extern uint64_t GetBit(uint64_t bitboard, uint8_t square);
	extern uint64_t PopBit(uint64_t bitboard, uint8_t square);
	extern uint64_t CountBits(uint64_t bitboard);

	extern uint8_t PopCount(uint64_t);
	extern void PrintBitboard(uint64_t bitboard);
	extern void PrintMove(uint32_t move);
	extern void PrintMoveSquare(uint32_t move);
	void PrintFullBoard(const GameState& gameState);

	extern std::vector<uint8_t> SerialiseBitboard(uint64_t bitboard);
	extern uint8_t BitScanForward(uint64_t bitboard);

	/* Magic Class */
	class Magic {
	public:
		uint8_t Square;
		bool Rook;
		uint64_t Mask;
		uint64_t MagicNumber;
		uint8_t IndexBits;

		Magic(uint8_t square, bool rook);
		Magic();
	};
};
