#include "types.h"

namespace Types {
	void PrintBitboardArray(uint64_t bitboard[], const int length) {
		std::cout << "{" << std::endl;
		for (int i = 0; i < length; i++) {
			std::cout << "0x" << std::setw(16) << std::setfill('0') << std::hex << bitboard[i] << ", ";
			if (i % 4 == 3)
				std::cout << std::endl;
		}
		std::cout << "};" << std::endl;
	}

	void PrintIndexArray(uint8_t index[], const int length) {
		std::cout << "{" << std::endl;
		for (int i = 0; i < length; i++) {
			std::cout << "0x" << std::setw(8) << std::setfill('0') << std::hex << static_cast<int>(index[i]) << ", ";
			if (i % 4 == 3)
				std::cout << std::endl;
		}
		std::cout << "};" << std::endl;
	}

	void PrintBitboard(const uint64_t bitboard) {
		for (int y = 7; y >= 0; y--) {
			for (int x = 0; x < 8; x++)
			{
				std::cout << ((bitboard >> (y * 8 + x)) & 1) << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
}
