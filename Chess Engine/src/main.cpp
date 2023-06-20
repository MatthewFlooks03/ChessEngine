#include "gamestate.h"
#include "tables.h"
#include "types.h"

int main()
{
	constexpr uint64_t bitboard = 0xFFFF00FFFFFFFFFFULL;
	std::list<uint8_t> list = Types::SerialiseBitboard(bitboard);
	return 0;
}
