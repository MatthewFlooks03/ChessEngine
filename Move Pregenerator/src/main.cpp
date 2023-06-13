#include "pch.h"
#include "types.h"
#include "tables.h"
#include "magic.h"

using namespace types;

int main()
{
	U64 magics[64];
	U8 indexBits[64];
	magic::generateBishopMagics(magics, indexBits);
	PrintBitboardArray(magics);
	PrintIndexArray(indexBits);
	
	magic::generateRookMagics(magics, indexBits);
	PrintBitboardArray(magics);
	PrintIndexArray(indexBits);

	return 0;
}
