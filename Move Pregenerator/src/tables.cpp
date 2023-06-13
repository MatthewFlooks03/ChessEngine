#include "pch.h"
#include "tables.h"

const void tables::knight(U64 moves[64] )
{
	//Pregenerate King Moves
	for (int pos = 0; pos < 64; pos++) {
		U64 piece = int_to_bitboard(pos);
			
		moves[pos] = north(north(east((piece))));
		moves[pos] = moves[pos] | north(north(west(piece)));
		moves[pos] = moves[pos] | south(south(east(piece)));
		moves[pos] = moves[pos] | south(south(west(piece)));
		moves[pos] = moves[pos] | east(east(north(piece)));
		moves[pos] = moves[pos] | east(east(south(piece)));
		moves[pos] = moves[pos] | west(west(north(piece)));
		moves[pos] = moves[pos] | west(west(south(piece)));
	}
}

const void tables::king(U64 moves[64])
{
	//Pregenerate King Moves
	for (int pos = 0; pos < 64; pos++) {
		U64 piece = int_to_bitboard(pos);

		moves[pos] = north(piece);
		moves[pos] = moves[pos] | south(piece);
		moves[pos] = moves[pos] | east(piece);
		moves[pos] = moves[pos] | west(piece);
		moves[pos] = moves[pos] | north_east(piece);
		moves[pos] = moves[pos] | north_west(piece);
		moves[pos] = moves[pos] | south_east(piece);
		moves[pos] = moves[pos] | south_west(piece);
	}
}

const void tables::whitePawnAttacks(U64 moves[64])
{
	//Pregenerate King Moves
	for (int pos = 0; pos < 64; pos++) {

		U64 piece = int_to_bitboard(pos);

		moves[pos] = north(east(piece));
		moves[pos] = moves[pos] | north(west(piece));

	}
}

const void tables::blackPawnAttacks(U64 moves[64])
{
	//Pregenerate King Moves
	for (int pos = 0; pos < 64; pos++) {

		U64 piece = int_to_bitboard(pos);

		moves[pos] = south(east(piece));
		moves[pos] = moves[pos] | south(west(piece));

	}
}

const void tables::whitePawnSingleMoves(U64 moves[64])
{
	//Pregenerate King Moves
	for (int pos = 0; pos < 64; pos++) {

		U64 piece = int_to_bitboard(pos);

		moves[pos] = north(piece);
	}
}

const void tables::blackPawnSingleMoves(U64 moves[64])
{
	//Pregenerate King Moves
	for (int pos = 0; pos < 64; pos++) {

		U64 piece = int_to_bitboard(pos);

		moves[pos] = south(piece);
	}
}

const void tables::rookMasks(U64 masks[64]) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			masks[i*8+j] = (((0x0101010101010101 << j) & ~(RANK_1 | RANK_8) )^ (((U64)0xFF << (i * 8)) & ~(FILE_A | FILE_H))) & ~(int_to_bitboard(i*8+j));
		}
	}
}

const void tables::bishopMasks(U64 masks[64]) {
	U64 NEmasks[16] = {
		0x8040201008040201, 0x4020100804020100, 0x2010080402010000, 0x1008040201000000,
		0x0804020100000000, 0x0402010000000000, 0x0201000000000000, 0x0100000000000000,
		0x0000000000000000, 0x0000000000000080, 0x0000000000008040, 0x0000000000804020,
		0x0000000080402010, 0x0000008040201008, 0x0000804020100804, 0x0080402010080402
	};

	U64 NWmasks[16] = {
		0x0102040810204080, 0x0001020408102040, 0x0000010204081020, 0x0000000102040810,
		0x0000000001020408, 0x0000000000010204, 0x0000000000000102, 0x0000000000000001,
		0x0000000000000000, 0x8000000000000000, 0x4080000000000000, 0x2040800000000000,
		0x1020408000000000, 0x0810204080000000, 0x0408102040800000, 0x0204081020408000
	};

	for (int i = 0; i < 64; i++)
	{
		int x = (int)i / 8;
		int y = i % 8;
		masks[i] = (NEmasks[(x - y) & 15] ^ NWmasks[(x + y) ^ 7]) & ~(RANK_1 | RANK_8 | FILE_A | FILE_H) & ~(int_to_bitboard(i));
	}
}


