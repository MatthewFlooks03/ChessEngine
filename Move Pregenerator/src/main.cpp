#include "types.h"
#include "Tables.h"
#include "magic.h"

using namespace Types;

int main()
{
	uint64_t magics[64];
	uint8_t indexBits[64];
	magic::GenerateBishopMagics(magics, indexBits);
	PrintBitboardArray(magics);
	PrintIndexArray(indexBits);
	
	magic::GenerateRookMagics(magics, indexBits);
	PrintBitboardArray(magics);
	PrintIndexArray(indexBits);

	return 0;
}
