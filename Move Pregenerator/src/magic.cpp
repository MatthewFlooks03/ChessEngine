#include "magic.h"
#include <random>
#include <map>


int magic::GetAllBlockers(uint64_t allBlockers[4096], const uint64_t andMask)
{
	uint64_t currentBlockers = 0;
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

uint64_t magic::MagicIndex(const Magic& magic, const uint64_t blockers)
{
	return ((blockers & magic.Mask) * magic.MagicNumber)>> (64 - magic.IndexBits);
}

bool magic::TryMakeTable(const Magic& magic, const int square, const bool rook)
{
	std::map<uint64_t, uint64_t> moveTable;

	auto* allBlockers = new uint64_t[4096];
	const int numBlockers = GetAllBlockers(allBlockers, magic.Mask);

	for (int n = 0; n < numBlockers; n++) {
		const uint64_t blockers = allBlockers[n];
		uint64_t index = MagicIndex(magic, blockers);

		uint64_t slidingMoves;
		if (rook) {
			slidingMoves = GetRookSlidingMoves(square, blockers);
		}
		else {
			slidingMoves = GetBishopSlidingMoves(square, blockers);	
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

uint64_t magic::GetRookSlidingMoves(const int square, const uint64_t blockers)
{
	uint64_t moves = 0;
	const int rank = square / 8;
	const int file = square % 8;
	// North
	for (int i = rank + 1; i < 8; i++) {
		moves |= (1ULL << (i * 8 + file));
		if (blockers & (1ULL << (i * 8 + file))) break;
	}
	// South
	for (int i = rank - 1; i >= 0; i--) {
		moves |= (1ULL << (i * 8 + file));
		if (blockers & (1ULL << (i * 8 + file))) break;
	}
	// East
	for (int i = file + 1; i < 8; i++) {
		moves |= (1ULL << (rank * 8 + i));
		if (blockers & (1ULL << (rank * 8 + i))) break;
	}
	// West
	for (int i = file - 1; i >= 0; i--) {
		moves |= (1ULL << (rank * 8 + i));
		if (blockers & (1ULL << (rank * 8 + i))) break;
	}
	return moves;
}

uint64_t magic::GetBishopSlidingMoves(const int square, const uint64_t blockers)
{
	uint64_t moves = 0;
	const int rank = square / 8;
	const int file = square % 8;
	// North East
	for (int i = 1; i < 8; i++) {
		if (rank + i > 7 || file + i > 7) break;
		moves |= (1ULL << ((rank + i) * 8 + file + i));
		if (blockers & (1ULL << ((rank + i) * 8 + file + i))) break;
	}
	// North West
	for (int i = 1; i < 8; i++) {
		if (rank + i > 7 || file - i < 0) break;
		moves |= (1ULL << ((rank + i) * 8 + file - i));
		if (blockers & (1ULL << ((rank + i) * 8 + file - i))) break;
	}
	// South East
	for (int i = 1; i < 8; i++) {
		if (rank - i < 0 || file + i > 7) break;
		moves |= (1ULL << ((rank - i) * 8 + file + i));
		if (blockers & (1ULL << ((rank - i) * 8 + file + i))) break;
	}
	// South West
	for (int i = 1; i < 8; i++) {
		if (rank - i < 0 || file - i < 0) break;
		moves |= (1ULL << ((rank - i) * 8 + file - i));
		if (blockers & (1ULL << ((rank - i) * 8 + file - i))) break;
	}
	return moves;
}

void magic::GenerateRookMagics(uint64_t magics[64], uint8_t indexBits[64]) {
	uint64_t masks[64];
	Tables::RookMasks(masks);

	GenerateMagics(magics, indexBits, masks, true);
}

void magic::GenerateBishopMagics(uint64_t magics[64], uint8_t indexBits[64]) {
	uint64_t masks[64];
	Tables::BishopMasks(masks);

	GenerateMagics(magics, indexBits, masks, false);
}

void magic::GenerateMagics(uint64_t magics[64], uint8_t indexBits[64], uint64_t masks[64], bool rook) {
	for (int square = 0; square < 64; square++) {
		Magic magic;
		magic.Mask = masks[square];

		uint8_t bits;
		uint64_t var = magic.Mask;
		for (bits = 0; var != 0; ++bits) var >>= 1;

		magic.IndexBits = bits;
		indexBits[square] = bits;

		do {
			std::random_device rd;
			std::mt19937_64 eng(rd());
			std::uniform_int_distribution<uint64_t> distribution;
			magic.MagicNumber = distribution(eng) & distribution(eng) & distribution(eng);
		} while (TryMakeTable(magic, square, rook));

		magics[square] = magic.MagicNumber;
	}
}
