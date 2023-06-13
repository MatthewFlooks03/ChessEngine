#include "pch.h"
#include "magic.h"

int magic::getAllBlockers(U64 allBlockers[4096], U64 andMask)
{
	U64 currentBlockers = 0;
	int i = 0;
	do {
		currentBlockers |= ~andMask;
		currentBlockers++;
		currentBlockers &= andMask;

		if (currentBlockers == 0) break;

		allBlockers[i] = currentBlockers;
		i++;
	} while (true);
	return i;
}

U64 magic::magicIndex(Magic magic, U64 blockers)
{
	blockers = blockers & magic.mask;
	U64 hash = blockers * magic.magic;
	U64 index = hash >> (64 - magic.indexBits);
	return index + magic.offset;
}

bool magic::tryMakeTable(Magic magic, int square, bool rook)
{
	std::map<U64, U64> moveTable;

	U64 *allBlockers = new U64[4096];
	int numBlockers = getAllBlockers(allBlockers, magic.mask);

	for (int n = 0; n < numBlockers; n++) {
		U64 blockers = allBlockers[n];
		U64 index = magicIndex(magic, blockers);
		
		U64 slidingMoves;
		if (rook) {
			slidingMoves = getRookSlidingMoves(square, blockers);
		}
		else {
			slidingMoves = getBishopSlidingMoves(square, blockers);	
		}

		if (moveTable.count(index) == 1) {
			if (moveTable[index] != slidingMoves) {
				delete[] allBlockers;
				return false;
			}
		} 
		else {
			moveTable[index] = slidingMoves;
		}
	}
	delete[] allBlockers;
	return true;
}

U64 magic::getRookSlidingMoves(int square, U64 blockers) {
	U64 moves = 0;
	int rank = square / 8;
	int file = square % 8;
	// North
	for (int i = rank + 1; i < 8; i++) {
		moves |= ((U64)1 << (i * 8 + file));
		if (blockers & ((U64)1 << (i * 8 + file))) break;
	}
	// South
	for (int i = rank - 1; i >= 0; i--) {
		moves |= ((U64)1 << (i * 8 + file));
		if (blockers & ((U64)1 << (i * 8 + file))) break;
	}
	// East
	for (int i = file + 1; i < 8; i++) {
		moves |= ((U64)1 << (rank * 8 + i));
		if (blockers & ((U64)1 << (rank * 8 + i))) break;
	}
	// West
	for (int i = file - 1; i >= 0; i--) {
		moves |= ((U64)1 << (rank * 8 + i));
		if (blockers & ((U64)1 << (rank * 8 + i))) break;
	}
	return moves;
}

U64 magic::getBishopSlidingMoves(int square, U64 blockers) {
	U64 moves = 0;
	int rank = square / 8;
	int file = square % 8;
	// North East
	for (int i = 1; i < 8; i++) {
		if (rank + i > 7 || file + i > 7) break;
		moves |= ((U64)1 << ((rank + i) * 8 + file + i));
		if (blockers & ((U64)1 << ((rank + i) * 8 + file + i))) break;
	}
	// North West
	for (int i = 1; i < 8; i++) {
		if (rank + i > 7 || file - i < 0) break;
		moves |= ((U64)1 << ((rank + i) * 8 + file - i));
		if (blockers & ((U64)1 << ((rank + i) * 8 + file - i))) break;
	}
	// South East
	for (int i = 1; i < 8; i++) {
		if (rank - i < 0 || file + i > 7) break;
		moves |= ((U64)1 << ((rank - i) * 8 + file + i));
		if (blockers & ((U64)1 << ((rank - i) * 8 + file + i))) break;
	}
	// South West
	for (int i = 1; i < 8; i++) {
		if (rank - i < 0 || file - i < 0) break;
		moves |= ((U64)1 << ((rank - i) * 8 + file - i));
		if (blockers & ((U64)1 << ((rank - i) * 8 + file - i))) break;
	}
	return moves;
}

void magic::generateRookMagics(U64 magics[64], U8 indexBits[64]) {
	U64 masks[64];
	tables::rookMasks(masks);

	generateMagics(magics, indexBits, masks, true);
}

void magic::generateBishopMagics(U64 magics[64], U8 indexBits[64]) {
	U64 masks[64];
	tables::bishopMasks(masks);

	generateMagics(magics, indexBits, masks, false);
}

void magic::generateMagics(U64 magics[64], U8 indexBits[64], U64 masks[64], bool rook) {
	Magic magic;

	for (int square = 0; square < 64; square++) {
		magic.mask = masks[square];

		U8 bits;
		U64 var = magic.mask;
		for (bits = 0; var != 0; ++bits) var >>= 1;

		magic.indexBits = bits;
		indexBits[square] = bits;

		do {
			std::random_device rd;
			std::mt19937_64 eng(rd());
			std::uniform_int_distribution<U64> distr;
			magic.magic = distr(eng) & distr(eng) & distr(eng);
		} while (tryMakeTable(magic, square, rook));

		magics[square] = magic.magic;
	}
}
