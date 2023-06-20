#include "gamestate.h"

GameState::GameState()
{
	WhiteKing = 0ULL;
	WhiteQueen = 0ULL;
	WhiteRook = 0ULL;
	WhiteBishop = 0ULL;
	WhiteKnight = 0ULL;
	WhitePawn = 0ULL;

	BlackKing = 0ULL;
	BlackQueen = 0ULL;
	BlackRook = 0ULL;
	BlackBishop = 0ULL;
	BlackKnight = 0ULL;
	BlackPawn = 0ULL;

	EnPassantSquare = 0ULL;

	CastlingRights = 0;

	SideToMove = Types::Color::White;
}

uint64_t GameState::operator[](const uint8_t bitboard) const
{
	switch(bitboard)
	{
		case 0:
			return WhiteKing;
		case 1:
			return WhiteQueen;
		case 2:
			return WhiteRook;
		case 3:
			return WhiteBishop;
		case 4:
			return WhiteKnight;
		case 5:
			return WhitePawn;
		case 6:
			return BlackKing;
		case 7:
			return BlackQueen;
		case 8:
			return BlackRook;
		case 9:
			return BlackBishop;
		case 10:
			return BlackKnight;
		case 11:
			return BlackPawn;
		case 12:
			return EnPassantSquare;
		default:
			throw std::invalid_argument("Invalid bitboard index");
	}
}

uint64_t & GameState::operator[](const uint8_t bitboard)
{
	switch(bitboard)
	{
		case 0:
			return WhiteKing;
		case 1:
			return WhiteQueen;
		case 2:
			return WhiteRook;
		case 3:
			return WhiteBishop;
		case 4:
			return WhiteKnight;
		case 5:
			return WhitePawn;
		case 6:
			return BlackKing;
		case 7:
			return BlackQueen;
		case 8:
			return BlackRook;
		case 9:
			return BlackBishop;
		case 10:
			return BlackKnight;
		case 11:
			return BlackPawn;
		case 12:
			return EnPassantSquare;
		default:
			throw std::invalid_argument("Invalid bitboard index");
	}
}


uint8_t GameState::GetPiece(const uint8_t square, const uint8_t color) const
{
	const uint8_t j = (color == Types::Color::White) ? 0 : 6;

	for (uint8_t i = j; i < j + 6; i++)
	{
		if (operator[](i) == Types::IntToBitboard(square))
		{
			return i - j;
		}
	}
	return Types::Piece::None;
}

bool GameState::ExecuteMove(const uint32_t move)
{
	const uint8_t color = static_cast<uint8_t>(move >> 22) & 1;
	const uint8_t piece = static_cast<uint8_t>(move >> 19) & 0b111;
	const uint8_t capture = static_cast<uint8_t>(move >> 16) & 0b111;
	const uint8_t castling = static_cast<uint8_t>(move >> 12) & 0b1111;
	const uint8_t initialPos = static_cast<uint8_t>(move >> 6) & 0b111111;
	const uint8_t finalPos = static_cast<uint8_t>(move) & 0b111111;

	const uint8_t offset = color == Types::Color::White ? 0 : 6;

	uint64_t bitboard = this->operator[](piece + offset);
	bitboard = Types::ClearBit(bitboard, initialPos);
	bitboard = Types::SetBit(bitboard, finalPos); 
	this->operator[](piece + offset) = bitboard;

	if(capture != Types::None)
	{
		uint64_t captureBitboard = this->operator[](capture + offset);
		captureBitboard = Types::ClearBit(captureBitboard, finalPos);
		this->operator[](capture + offset) = captureBitboard;
	}


	// TODO: Check for check
	bool check = false;
	if(check)
	{
		ReverseMove(move);
		return false;
	}

	// TODO: Check for castling through check (need attacked squares bitboard)
	if(castling != 0)
	{
		uint8_t rookInitialPos = 0;
		uint8_t rookFinalPos = 0;
		bool legal = false;
		switch(castling)
		{
			case Types::CastlingRights::WhiteKingSide:
				rookInitialPos = 63;
				rookFinalPos = 61;
				break;
			case Types::CastlingRights::WhiteQueenSide:
				rookInitialPos = 56;
				rookFinalPos = 59;
				break;
			case Types::CastlingRights::BlackKingSide:
				rookInitialPos = 7;
				rookFinalPos = 5;
				break;
			case Types::CastlingRights::BlackQueenSide:
				rookInitialPos = 0;
				rookFinalPos = 3;
				break;
			default:
				throw std::invalid_argument("Invalid castling rights");
		}
		uint64_t rookBitboard = this->operator[](Types::Piece::Rook + offset);
		rookBitboard = Types::ClearBit(rookBitboard, rookInitialPos);
		rookBitboard = Types::SetBit(rookBitboard, rookFinalPos);
		this->operator[](Types::Piece::Rook + offset) = rookBitboard;
	}
	return true;
}

void GameState::ReverseMove(const uint32_t move)
{
	const uint8_t color = static_cast<uint8_t>(move >> 22) & 1;
	const uint8_t piece = static_cast<uint8_t>(move >> 19) & 0b111;
	const uint8_t capture = static_cast<uint8_t>(move >> 16) & 0b111;
	const uint8_t castling = static_cast<uint8_t>(move >> 12) & 0b1111;
	const uint8_t initialPos = static_cast<uint8_t>(move >> 6) & 0b111111;
	const uint8_t finalPos = static_cast<uint8_t>(move) & 0b111111;

	const uint8_t offset = color == Types::Color::White ? 0 : 6;

	uint64_t bitboard = this->operator[](piece + offset);
	bitboard = Types::ClearBit(bitboard, finalPos);
	bitboard = Types::SetBit(bitboard, initialPos); 
	this->operator[](piece + offset) = bitboard;

	if(capture != Types::None)
	{
		uint64_t captureBitboard = this->operator[](capture + offset);
		captureBitboard = Types::SetBit(captureBitboard, finalPos);
		this->operator[](capture + offset) = captureBitboard;
	}
}
