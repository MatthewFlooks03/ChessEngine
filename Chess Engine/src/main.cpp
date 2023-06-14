#include "tables.h"
#include "pregeneration.h"

int main()
{
	PreGeneration::Generate();

	Tables::RookMagicTesting();
	Tables::BishopMagicTesting();
	
	return 0;
}
