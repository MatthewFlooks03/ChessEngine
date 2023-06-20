#include "pregeneration.h"
#include "tables.h"
#include <iomanip>
#include <random>
#include <unordered_map>
#include <bitset>

using namespace Types;

void PreGeneration::Generate()
{
	uint64_t bishopMagics[64];
	uint8_t bishopIndexBits[64];
	uint64_t rookMagics[64];
	uint8_t rookIndexBits[64];

	GenerateBishopMagics(bishopMagics, bishopIndexBits);
	GenerateRookMagics(rookMagics, rookIndexBits);

	std::cout << "constexpr uint64_t Tables::ROOK_MAGICS[64] = {" << std::endl;
	PrintBitboardArray(rookMagics);
	std::cout << "};" << std::endl;

	std::cout << "constexpr uint64_t Tables::BISHOP_MAGICS[64] = {" << std::endl;
	PrintBitboardArray(bishopMagics);
	std::cout << "};" << std::endl;
}

/*************************/

void PreGeneration::GetKing(uint64_t moves[64])
{
	for (int pos = 0; pos < 64; pos++)
	{
		const uint64_t piece = IntToBitboard(pos);

		moves[pos] = North(piece);
		moves[pos] = moves[pos] | South(piece);
		moves[pos] = moves[pos] | East(piece);
		moves[pos] = moves[pos] | West(piece);
		moves[pos] = moves[pos] | NorthEast(piece);
		moves[pos] = moves[pos] | NorthWest(piece);
		moves[pos] = moves[pos] | SouthEast(piece);
		moves[pos] = moves[pos] | SouthWest(piece);
	}
}

void PreGeneration::GetKnight(uint64_t moves[64])
{
	for (int pos = 0; pos < 64; pos++)
	{
		const uint64_t piece = IntToBitboard(pos);

		moves[pos] = North(North(East((piece))));
		moves[pos] = moves[pos] | North(North(West(piece)));
		moves[pos] = moves[pos] | South(South(East(piece)));
		moves[pos] = moves[pos] | South(South(West(piece)));
		moves[pos] = moves[pos] | East(East(North(piece)));
		moves[pos] = moves[pos] | East(East(South(piece)));
		moves[pos] = moves[pos] | West(West(North(piece)));
		moves[pos] = moves[pos] | West(West(South(piece)));
	}
}

void PreGeneration::GetWhitePawnAttacks(uint64_t moves[64])
{
	for (int pos = 0; pos < 64; pos++)
	{
		const uint64_t piece = IntToBitboard(pos);

		moves[pos] = North(East(piece));
		moves[pos] = moves[pos] | North(West(piece));
	}
}

void PreGeneration::GetBlackPawnAttacks(uint64_t moves[64])
{
	for (int pos = 0; pos < 64; pos++)
	{
		const uint64_t piece = IntToBitboard(pos);

		moves[pos] = South(East(piece));
		moves[pos] = moves[pos] | South(West(piece));
	}
}

void PreGeneration::GetWhitePawnSinglePush(uint64_t moves[64])
{
	for (int pos = 0; pos < 64; pos++)
	{
		const uint64_t piece = IntToBitboard(pos);

		moves[pos] = North(piece);
	}
}

void PreGeneration::GetBlackPawnSinglePush(uint64_t moves[64])
{
	for (int pos = 0; pos < 64; pos++)
	{
		const uint64_t piece = IntToBitboard(pos);

		moves[pos] = South(piece);
	}
}

void PreGeneration::GetWhitePawnDoublePush(uint64_t moves[64])
{
	for (int pos = 0; pos < 64; pos++)
	{
		const uint64_t piece = IntToBitboard(pos);

		moves[pos] = North(North(piece));
	}
}

void PreGeneration::GetBlackPawnDoublePush(uint64_t moves[64])
{
	for (int pos = 0; pos < 64; pos++)
	{
		const uint64_t piece = IntToBitboard(pos);

		moves[pos] = South(South(piece));
	}
}

void PreGeneration::GetRookMasks(uint64_t masks[64])
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			masks[i * 8 + j] = (((0x0101010101010101 << j) & ~(RANK_1 | RANK_8)) ^ ((0xFFULL << (i * 8)) & ~(FILE_A |
				FILE_H))) & ~(IntToBitboard(i * 8 + j));
		}
	}
}

void PreGeneration::GetBishopMasks(uint64_t masks[64])
{
	constexpr uint64_t northEastMasks[16] = {
		0x8040201008040201, 0x4020100804020100, 0x2010080402010000, 0x1008040201000000,
		0x0804020100000000, 0x0402010000000000, 0x0201000000000000, 0x0100000000000000,
		0x0000000000000000, 0x0000000000000080, 0x0000000000008040, 0x0000000000804020,
		0x0000000080402010, 0x0000008040201008, 0x0000804020100804, 0x0080402010080402
	};

	constexpr uint64_t northWestMasks[16] = {
		0x0102040810204080, 0x0001020408102040, 0x0000010204081020, 0x0000000102040810,
		0x0000000001020408, 0x0000000000010204, 0x0000000000000102, 0x0000000000000001,
		0x0000000000000000, 0x8000000000000000, 0x4080000000000000, 0x2040800000000000,
		0x1020408000000000, 0x0810204080000000, 0x0408102040800000, 0x0204081020408000
	};

	for (int i = 0; i < 64; i++)
	{
		const int x = (int)i / 8;
		const int y = i % 8;
		masks[i] = (northEastMasks[(x - y) & 15] ^ northWestMasks[(x + y) ^ 7]) & ~(RANK_1 | RANK_8 | FILE_A | FILE_H) &
			~(IntToBitboard(i));
	}
}

void PreGeneration::PrintBitboardArray(uint64_t bitboard[], int length)
{
	for (int i = 0; i < length; i++)
	{
		std::cout << "0x" << std::setw(16) << std::setfill('0') << std::hex << bitboard[i] << ", ";
		if (i % 4 == 3)
			std::cout << std::endl;
	}
}

void PreGeneration::PrintIndexArray(uint8_t index[], int length)
{
	for (int i = 0; i < length; i++)
	{
		std::cout << "0x" << std::setw(8) << std::setfill('0') << std::hex << static_cast<int>(index[i]) << ", ";
		if (i % 4 == 3)
			std::cout << std::endl;
	}
}

void PreGeneration::GenerateRookMagics(uint64_t magics[64], uint8_t indexBits[64])
{
	uint64_t masks[64];
	GetRookMasks(masks);
	GenerateMagics(magics, indexBits, masks, true);
}

void PreGeneration::GenerateBishopMagics(uint64_t magics[64], uint8_t indexBits[64])
{
	uint64_t masks[64];
	GetBishopMasks(masks);
	GenerateMagics(magics, indexBits, masks, false);
}

void PreGeneration::GenerateMagics(uint64_t magics[64], uint8_t indexBits[64], uint64_t masks[64], bool rook)
{
}

uint64_t PreGeneration::GetRookSlidingMoves(int square, uint64_t blockers)
{
	uint64_t moves = 0;
	const int rank = square / 8;
	const int file = square % 8;
	// North
	for (int i = rank + 1; i < 8; i++)
	{
		moves |= (1ULL << (i * 8 + file));
		if (blockers & (1ULL << (i * 8 + file))) break;
	}
	// South
	for (int i = rank - 1; i >= 0; i--)
	{
		moves |= (1ULL << (i * 8 + file));
		if (blockers & (1ULL << (i * 8 + file))) break;
	}
	// East
	for (int i = file + 1; i < 8; i++)
	{
		moves |= (1ULL << (rank * 8 + i));
		if (blockers & (1ULL << (rank * 8 + i))) break;
	}
	// West
	for (int i = file - 1; i >= 0; i--)
	{
		moves |= (1ULL << (rank * 8 + i));
		if (blockers & (1ULL << (rank * 8 + i))) break;
	}
	return moves;
}

uint64_t PreGeneration::GetBishopSlidingMoves(int square, uint64_t blockers)
{
	uint64_t moves = 0;
	const int rank = square / 8;
	const int file = square % 8;
	// North East
	for (int i = 1; i < 8; i++)
	{
		if (rank + i > 7 || file + i > 7) break;
		moves |= (1ULL << ((rank + i) * 8 + file + i));
		if (blockers & (1ULL << ((rank + i) * 8 + file + i))) break;
	}
	// North West
	for (int i = 1; i < 8; i++)
	{
		if (rank + i > 7 || file - i < 0) break;
		moves |= (1ULL << ((rank + i) * 8 + file - i));
		if (blockers & (1ULL << ((rank + i) * 8 + file - i))) break;
	}
	// South East
	for (int i = 1; i < 8; i++)
	{
		if (rank - i < 0 || file + i > 7) break;
		moves |= (1ULL << ((rank - i) * 8 + file + i));
		if (blockers & (1ULL << ((rank - i) * 8 + file + i))) break;
	}
	// South West
	for (int i = 1; i < 8; i++)
	{
		if (rank - i < 0 || file - i < 0) break;
		moves |= (1ULL << ((rank - i) * 8 + file - i));
		if (blockers & (1ULL << ((rank - i) * 8 + file - i))) break;
	}
	return moves;
}
