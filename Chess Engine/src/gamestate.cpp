#include "gamestate.h"
#include "movegeneration.h"
#include <sstream>

#include "tables.h"

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

	Hash = 0;
	GenerateHash();

	PreviousState = nullptr;
	NextState = nullptr;
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
		const uint8_t square = (segments[3][0] - 'a') + (segments[3][1] - '1')*8;
		EnPassantSquare = Types::IntToBitboard(square);
	}

	// TODO: Finish Parsing HMC and FMC

	PreviousState = nullptr;
	NextState = nullptr;
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
	CastlingRights = gameState->CastlingRights;
	SideToMove = gameState->SideToMove;
	Hash = gameState->Hash;
	PreviousState = nullptr;
	NextState = nullptr;
}

uint8_t GameState::FenIntDecode(const uint8_t i)
{
	return (7-i/8)*8 + i%8;
}

uint64_t GameState::operator[](const uint8_t& bitboard) const
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
uint64_t & GameState::operator[](const uint8_t& bitboard)
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

bool GameState::operator==(const GameState& gs) const
{
	const bool result = 
			this->WhiteKing == gs.WhiteKing &&
			this->WhiteQueen == gs.WhiteQueen &&
			this->WhiteRook == gs.WhiteRook &&
			this->WhiteBishop == gs.WhiteBishop &&
			this->WhiteKnight == gs.WhiteKnight &&
			this->WhitePawn == gs.WhitePawn &&
			this->BlackKing == gs.BlackKing &&
			this->BlackQueen == gs.BlackQueen &&
			this->BlackRook == gs.BlackRook &&
			this->BlackBishop == gs.BlackBishop &&
			this->BlackKnight == gs.BlackKnight &&
			this->BlackPawn == gs.BlackPawn &&
			this->EnPassantSquare == gs.EnPassantSquare &&
			this->CastlingRights == gs.CastlingRights &&
			this->SideToMove == gs.SideToMove &&
			this->MoveHistory == gs.MoveHistory;
	return result;
}

bool GameState::operator!=(const GameState& gs) const
{
	return !(*this == gs);
}

void GameState::GetDifference(const GameState& gs) const
{
	std::cout << "Differences in:" << std::endl;

	if (this->WhiteKing != gs.WhiteKing) {
		std::cout << "\t WhiteKing" << std::endl;
	}
	if (this->WhiteQueen != gs.WhiteQueen) {
		std::cout << "\t WhiteQueen" << std::endl;
	}
	if (this->WhiteBishop != gs.WhiteBishop) {
		std::cout << "\t WhiteBishop" << std::endl;
	}
	if (this->WhiteRook != gs.WhiteRook) {
		std::cout << "\t WhiteRook" << std::endl;
	}
	if (this->WhiteKnight != gs.WhiteKnight) {
		std::cout << "\t WhiteKnight" << std::endl;
	}
	if (this->WhitePawn != gs.WhitePawn) {
		std::cout << "\t WhitePawn" << std::endl;
	}
	if (this->BlackKing != gs.BlackKing) {
		std::cout << "\t BlackKing" << std::endl;
	}
	if (this->BlackQueen != gs.BlackQueen) {
		std::cout << "\t BlackQueen" << std::endl;
	}
	if (this->BlackBishop != gs.BlackBishop) {
		std::cout << "\t BlackBishop" << std::endl;
	}
	if (this->BlackKnight != gs.BlackKnight) {
		std::cout << "\t BlackKnight" << std::endl;
	}
	if (this->BlackPawn != gs.BlackPawn) {
		std::cout << "\t BlackPawn" << std::endl;
	}
	if (this->EnPassantSquare != gs.EnPassantSquare) {
		std::cout << "\t EnPassantSquare" << std::endl;
	}
	if (this->CastlingRights != gs.CastlingRights) {
		std::cout << "\t CastlingRights" << std::endl;
	}
	if (this->SideToMove != gs.SideToMove) {
		std::cout << "\t SideToMove" << std::endl;
	}
	if (this->MoveHistory->back() != gs.MoveHistory->back()) {
		std::cout << "\t MoveHistory" << std::endl;
	}
}

uint8_t GameState::GetPiece(const uint8_t square, const uint8_t color) const
{
	const uint64_t squareBitboard = Types::IntToBitboard(square);
	const uint8_t j = (color == Types::Color::White) ? 0 : 6;

	for (uint8_t i = j; i < j + 6; i++)
	{
		if (operator[](i) & squareBitboard)
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




void GameState::NextTurn()
{
	this->SideToMove = this->SideToMove == Types::White ? Types::Black : Types::White;
}


void GameState::PreviousTurn()
{
	this->SideToMove = this->SideToMove == Types::White ? Types::Black : Types::White;
}


void GameState::UpdateHash(uint32_t move)
{
	
}

void GameState::GenerateHash()
{
	Hash = 0;

	for (auto i = 0; i < 12; i++)
	{
		std::vector<uint8_t> pieces = Types::SerialiseBitboard(this->operator[](i + 8 * (SideToMove == Types::Color::Black)));
		for(auto const square : pieces)
		{
			Hash ^= Tables::ZobristTable[square][i];
		}
	}

	Hash ^= Tables::ZobristTable[EnPassantSquare][12];
	Hash ^= Tables::ZobristSideToMove[this->SideToMove];
	Hash ^= Tables::ZobristCastlingRights[this->CastlingRights];
}

