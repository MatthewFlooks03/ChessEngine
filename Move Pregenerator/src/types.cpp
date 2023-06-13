#include "pch.h"
#include "types.h"

namespace types {
	void PrintBitboardArray(U64 bitboard[], int length) {
		std::cout << "{" << std::endl;
		for (int i = 0; i < length; i++) {
			std::cout << "0x" << std::setw(16) << std::setfill('0') << std::hex << bitboard[i] << ", ";
			if (i % 4 == 3)
				std::cout << std::endl;
		}
		std::cout << "};" << std::endl;
	}

	void PrintIndexArray(U8 index[], int length) {
		std::cout << "{" << std::endl;
		for (int i = 0; i < length; i++) {
			std::cout << "0x" << std::setw(16) << std::setfill('0') << std::hex << (int)index[i] << ", ";
			if (i % 4 == 3)
				std::cout << std::endl;
		}
		std::cout << "};" << std::endl;
	}

	void types::PrintBitboard(U64 bitboard) {
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
