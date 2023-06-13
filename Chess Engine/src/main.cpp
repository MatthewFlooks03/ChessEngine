#include "tables.h"

int main()
{
	auto* tables = new Tables();

	uint64_t result = tables->GetRookMoves(0, 0x4202000a242020);

	Types:PrintBitboard(result);

	return 0;
}
