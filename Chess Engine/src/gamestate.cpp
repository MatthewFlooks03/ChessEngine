#include "gamestate.h"
#include "movegeneration.h"
#include <sstream>

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
	PreviousEnPassantSquare = 0ULL;

	CastlingRights = 0;

	SideToMove = Types::Color::White;

	MoveHistory = new std::list<uint32_t>;
}
GameState::GameState(const std::string& fen) : GameState()
{
	// Split FEN
	std::string segments[6];
	std::stringstream fenStringStream(fen);
	uint8_t i = 0;
	while (fenStringStream.good() && i < 6)
	{
		fenStringStream >> segments[i];
		++i;
	}

	// Parse pieces
	i = 0;
	for(const auto &ch : segments[0])
	{
		switch(ch)
		{
			case 'k':
				BlackKing |= Types::IntToBitboard(FenIntDecode(i));
				break;
			case 'q':
				BlackQueen |= Types::IntToBitboard(FenIntDecode(i));
				break;
			case 'r':
				BlackRook |= Types::IntToBitboard(FenIntDecode(i));
				break;
			case 'b':
				BlackBishop |= Types::IntToBitboard(FenIntDecode(i));
				break;
			case 'n':
				BlackKnight |= Types::IntToBitboard(FenIntDecode(i));
				break;
			case 'p':
				BlackPawn |= Types::IntToBitboard(FenIntDecode(i));
				break;
			case 'K':
				WhiteKing |= Types::IntToBitboard(FenIntDecode(i));
				break;
			case 'Q':
				WhiteQueen |= Types::IntToBitboard(FenIntDecode(i));
				break;
			case 'R':
				WhiteRook |= Types::IntToBitboard(FenIntDecode(i));
				break;
			case 'B':
				WhiteBishop |= Types::IntToBitboard(FenIntDecode(i));
				break;
			case 'N':
				WhiteKnight |= Types::IntToBitboard(FenIntDecode(i));
				break;
			case 'P':
				WhitePawn |= Types::IntToBitboard(FenIntDecode(i));
				break;
			case '/':
				i += 8 - (i - 1) % 8 - 2;
				break;
			default:
				if(ch >= '1' && ch <= '8')
				{
					i += ch - '0' - 1;
				}
				else
				{
					throw std::invalid_argument("Invalid FEN string");
				}
				break;
		}
		i++;
	}

	// Parse side to move
	if(segments[1] == "w")
	{
		SideToMove = Types::Color::White;
	}
	else if(segments[1] == "b")
	{
		SideToMove = Types::Color::Black;
	}
	else
	{
		throw std::invalid_argument("Invalid FEN string");
	}

	// Parse castling rights
	for(const auto &ch : segments[2])
	{
		switch(ch)
		{
			case 'K':
				CastlingRights |= Types::CastlingRights::WhiteKingSide;
				break;
			case 'Q':
				CastlingRights |= Types::CastlingRights::WhiteQueenSide;
				break;
			case 'k':
				CastlingRights |= Types::CastlingRights::BlackKingSide;
				break;
			case 'q':
				CastlingRights |= Types::CastlingRights::BlackQueenSide;
				break;
			case '-':
				break;
			default:
				throw std::invalid_argument("Invalid FEN string");
		}
	}

	// Parse en passant square
	if(segments[3] != "-")
	{
		EnPassantSquare = Types::IntToBitboard((segments[3][0] - 'a') + (segments[3][1] - '1')*8);
	}

	// TODO: Finish Parsing HMC and FMC
}
GameState::GameState(const GameState* gameState)
{
	WhiteKing = gameState->WhiteKing;
	WhiteQueen = gameState->WhiteQueen;
	WhiteRook = gameState->WhiteRook;
	WhiteBishop = gameState->WhiteBishop;
	WhiteKnight = gameState->WhiteKnight;
	WhitePawn = gameState->WhitePawn;
	BlackKing = gameState->BlackKing;
	BlackQueen = gameState->BlackQueen;
	BlackRook = gameState->BlackRook;
	BlackBishop = gameState->BlackBishop;
	BlackKnight = gameState->BlackKnight;
	BlackPawn = gameState->BlackPawn;
	EnPassantSquare = gameState->EnPassantSquare;
	PreviousEnPassantSquare = gameState->PreviousEnPassantSquare;
	CastlingRights = gameState->CastlingRights;
	SideToMove = gameState->SideToMove;
	MoveHistory = gameState->MoveHistory;
}

uint8_t GameState::FenIntDecode(const uint8_t i)
{
	return (7-i/8)*8 + i%8;
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
	const uint64_t squareBitboard = Types::IntToBitboard(square);
	const uint8_t j = (color == Types::Color::White) ? 0 : 6;

	for (uint8_t i = j; i < j + 6; i++)
	{
		if (operator[](i) == squareBitboard)
		{
			return i - j;
		}
	}
	if (EnPassantSquare == squareBitboard)
	{
		return Types::EnPassant;
	}
	return Types::Piece::None;
}

bool GameState::ExecuteMove(const uint32_t move)
{
	const uint8_t color = (move >> 31) & 0b1;
	const uint8_t pieceMoved = (move >> 28) & 0b111;
	const uint8_t pieceCaptured = (move >> 25) & 0b111;
	const uint8_t initialPosition = (move >> 19) & 0b111111;
	const uint8_t finalPosition = (move >> 13) & 0b111111;
	const uint8_t enPassant = (move >> 7) & 0b111111;
	const uint8_t promotion = (move >> 4) & 0b111;
	const uint8_t castling = move & 0b1111;

	const uint8_t offset = color == Types::Color::White ? 0 : 6;

	uint64_t bitboard = this->operator[](pieceMoved + offset);

	/* Move Piece */
	bitboard = Types::ClearBit(bitboard, initialPosition);
	bitboard = Types::SetBit(bitboard, finalPosition); 
	this->operator[](pieceMoved + offset) = bitboard;

	/* Capture Checks */
	if(pieceCaptured == Types::EnPassant) 
	{
		uint64_t captureBitboard = this->operator[](Types::Pawn + offset);
		const uint8_t pawnSquare = color == Types::White ? finalPosition - 8 : finalPosition + 8;
		captureBitboard = Types::ClearBit(captureBitboard, pawnSquare);
		this->operator[](Types::Pawn + offset) = captureBitboard;
	}
	else if(pieceCaptured != Types::None)
	{
		uint64_t captureBitboard = this->operator[](pieceCaptured + offset);
		captureBitboard = Types::ClearBit(captureBitboard, finalPosition);
		this->operator[](pieceCaptured + offset) = captureBitboard;
	}

	/* Promotion Checks */
	const uint8_t promotionRank = color == Types::White ? 7 : 0;
	if(pieceMoved == Types::Pawn && Types::GetRank(finalPosition) == promotionRank)
	{
		this->operator[](pieceMoved + offset) = Types::ClearBit(bitboard, finalPosition);

		this->operator[](promotion + offset) = Types::SetBit(bitboard, finalPosition);
	}

	/* Castling Checks */
	const uint8_t oppositeColor = color == Types::White ? Types::Black : Types::White;
	if(castling != 0)
	{
		uint8_t rookInitialPos;
		uint8_t rookFinalPos;
		bool legal = false;
		switch(castling)
		{
			case Types::CastlingRights::WhiteKingSide:
				legal = !(MoveGeneration::GetAllAttacks(*this, oppositeColor) & 0x0000000000000060);
				rookInitialPos = 63;
				rookFinalPos = 61;
				break;
			case Types::CastlingRights::WhiteQueenSide:
				legal = !(MoveGeneration::GetAllAttacks(*this, oppositeColor) & 0x000000000000000E);
				rookInitialPos = 56;
				rookFinalPos = 59;
				break;
			case Types::CastlingRights::BlackKingSide:
				legal = !(MoveGeneration::GetAllAttacks(*this, oppositeColor) & 0x6000000000000000);
				rookInitialPos = 7;
				rookFinalPos = 5;
				break;
			case Types::CastlingRights::BlackQueenSide:
				legal = !(MoveGeneration::GetAllAttacks(*this, oppositeColor) & 0xE00000000000000);
				rookInitialPos = 0;
				rookFinalPos = 3;
				break;
			default:
				throw std::invalid_argument("Invalid castling rights");
		}
		if(legal) // Move Rook
		{
			uint64_t rookBitboard = this->operator[](Types::Piece::Rook + offset);
			rookBitboard = Types::ClearBit(rookBitboard, rookInitialPos);
			rookBitboard = Types::SetBit(rookBitboard, rookFinalPos);
			this->operator[](Types::Piece::Rook + offset) = rookBitboard;
				
			this->CastlingRights ^= castling; // Update Castling Rights
		}
	}

	/* Add En Passant Square */
	this->PreviousEnPassantSquare = this->EnPassantSquare;
	if(enPassant != Types::None)
	{
		this->EnPassantSquare = Types::IntToBitboard(enPassant);
	}
	else
	{
		this->EnPassantSquare = 0;
	}

	/* Add Move to History */
	this->MoveHistory->push_back(move);

	/* Update Turn */
	this->NextTurn();

	/* Check for Check */
	const uint64_t kingBitboard = color == Types::White ? this->WhiteKing : this->BlackKing;
	if(kingBitboard & MoveGeneration::GetAllAttacks(*this, oppositeColor))
	{
		ReverseMove(move);
		return false;
	}

	return true;
}

void GameState::ReverseMove(const uint32_t move)
{
	const uint8_t color = (move >> 31) & 0b1;
	const uint8_t pieceMoved = (move >> 28) & 0b111;
	const uint8_t pieceCaptured = (move >> 25) & 0b111;
	const uint8_t initialPosition = (move >> 19) & 0b111111;
	const uint8_t finalPosition = (move >> 13) & 0b111111;
	const uint8_t enPassant = (move >> 7) & 0b111111;
	const uint8_t promotion = (move >> 4) & 0b111;
	const uint8_t castling = move & 0b1111;

	const uint8_t offset = color == Types::Color::White ? 0 : 6;

	uint64_t bitboard = this->operator[](pieceMoved + offset);

	/* Move Piece */
	bitboard = Types::SetBit(bitboard, initialPosition);
	bitboard = Types::ClearBit(bitboard, finalPosition); 
	this->operator[](pieceMoved + offset) = bitboard;

	/* Capture Checks */
	if(pieceCaptured == Types::EnPassant) 
	{
		uint64_t captureBitboard = this->operator[](Types::Pawn + offset);
		const uint8_t pawnSquare = color == Types::White ? finalPosition - 8 : finalPosition + 8;
		captureBitboard = Types::SetBit(captureBitboard, pawnSquare);
		this->operator[](Types::Pawn + offset) = captureBitboard;
	}
	else if(pieceCaptured != Types::None)
	{
		uint64_t captureBitboard = this->operator[](pieceCaptured + offset);
		captureBitboard = Types::SetBit(captureBitboard, finalPosition);
		this->operator[](pieceCaptured + offset) = captureBitboard;
	}

	/* Promotion Checks */
	const uint8_t promotionRank = color == Types::White ? 7 : 0;
	if(pieceMoved == Types::Pawn && Types::GetRank(finalPosition) == promotionRank)
	{
		this->operator[](pieceMoved + offset) = Types::SetBit(bitboard, finalPosition);

		this->operator[](promotion + offset) = Types::ClearBit(bitboard, finalPosition);
	}

	/* Castling Checks */
	const uint8_t oppositeColor = color == Types::White ? Types::Black : Types::White;
	if(castling != 0)
	{
		uint8_t rookInitialPos;
		uint8_t rookFinalPos;
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
		rookBitboard = Types::SetBit(rookBitboard, rookInitialPos);
		rookBitboard = Types::ClearBit(rookBitboard, rookFinalPos);
		this->operator[](Types::Piece::Rook + offset) = rookBitboard;
				
		this->CastlingRights ^= castling; // Update Castling Rights
	}

	/* Add En Passant Square */
	this->EnPassantSquare = PreviousEnPassantSquare;

	/* Remove Move from History */
	this->MoveHistory->pop_back();

	/* Switch Turn */
	this->PreviousTurn();
}

void GameState::NextTurn()
{
	this->SideToMove = this->SideToMove == Types::White ? Types::Black : Types::White;
}

void GameState::PreviousTurn()
{
	NextTurn();
}


