#include "Tables.h"

void Tables::Knight(uint64_t moves[64])
{
	// Pre-generate King Moves
	for (int pos = 0; pos < 64; pos++) {
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

void Tables::King(uint64_t moves[64])
{
	//Pre-generate King Moves
	for (int pos = 0; pos < 64; pos++) {
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

void Tables::WhitePawnAttacks(uint64_t moves[64])
{
	//Pre-generate King Moves
	for (int pos = 0; pos < 64; pos++) {
		const uint64_t piece = IntToBitboard(pos);

		moves[pos] = North(East(piece));
		moves[pos] = moves[pos] | North(West(piece));
	}
}

void Tables::BlackPawnAttacks(uint64_t moves[64])
{
	//Pre-generate King Moves
	for (int pos = 0; pos < 64; pos++) {
		const uint64_t piece = IntToBitboard(pos);

		moves[pos] = South(East(piece));
		moves[pos] = moves[pos] | South(West(piece));

	}
}

void Tables::WhitePawnSingleMoves(uint64_t moves[64])
{
	//Pre-generate King Moves
	for (int pos = 0; pos < 64; pos++) {
		const uint64_t piece = IntToBitboard(pos);

		moves[pos] = North(piece);
	}
}

void Tables::BlackPawnSingleMoves(uint64_t moves[64])
{
	//Pre-generate King Moves
	for (int pos = 0; pos < 64; pos++) {
		const uint64_t piece = IntToBitboard(pos);

		moves[pos] = South(piece);
	}
}

void Tables::RookMasks(uint64_t masks[64]) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			masks[i*8+j] = (((0x0101010101010101 << j) & ~(RANK_1 | RANK_8) )^ ((0xFFULL << (i * 8)) & ~(FILE_A | FILE_H))) & ~(IntToBitboard(i*8+j));
		}
	}
}

void Tables::BishopMasks(uint64_t masks[64]) {
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
		masks[i] = (northEastMasks[(x - y) & 15] ^ northWestMasks[(x + y) ^ 7]) & ~(RANK_1 | RANK_8 | FILE_A | FILE_H) & ~(IntToBitboard(i));
	}
}


