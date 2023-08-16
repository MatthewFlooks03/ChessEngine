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
	CastlingRights = gameState->CastlingRights;
	SideToMove = gameState->SideToMove;
	MoveHistory = gameState->MoveHistory;
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
	if (this->MoveHistory != gs.MoveHistory) {
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

bool GameState::OldExecuteMove(const uint32_t move)
{
	/* Add Move to History */
	this->MoveHistory->push_back(move);

	const uint8_t color = (move >> 31) & 0b1;
	const uint8_t pieceMoved = (move >> 28) & 0b111;
	const uint8_t pieceCaptured = (move >> 25) & 0b111;
	const uint8_t initialPosition = (move >> 19) & 0b111111;
	const uint8_t finalPosition = (move >> 13) & 0b111111;
	const uint8_t enPassant = (move >> 7) & 0b111111;
	const uint8_t promotion = (move >> 4) & 0b111;
	const uint8_t castling = move & 0b1111;

	const uint8_t offset = color == Types::Color::White ? 0 : 6;
	const uint8_t oppositeOffset = color == Types::Color::White ? 6 : 0;

	uint64_t bitboard = this->operator[](pieceMoved + offset);

	/* Move Piece */
	bitboard = Types::ClearBit(bitboard, initialPosition);
	bitboard = Types::SetBit(bitboard, finalPosition); 
	this->operator[](pieceMoved + offset) = bitboard;

	/* Capture Checks */
	if(pieceCaptured == Types::EnPassant && pieceMoved == Types::Pawn) 
	{
		uint64_t captureBitboard = this->operator[](Types::Pawn + oppositeOffset);
		const uint8_t pawnSquare = color == Types::White ? finalPosition - 8 : finalPosition + 8;
		captureBitboard = Types::ClearBit(captureBitboard, pawnSquare);
		this->operator[](Types::Pawn + oppositeOffset) = captureBitboard;
	}
	else if(pieceCaptured != Types::None && pieceCaptured != Types::EnPassant)
	{
		uint64_t captureBitboard = this->operator[](pieceCaptured + oppositeOffset);
		captureBitboard = Types::ClearBit(captureBitboard, finalPosition);
		this->operator[](pieceCaptured + oppositeOffset) = captureBitboard;
	}

	/* Promotion Checks */
	const uint8_t promotionRank = color == Types::White ? 7 : 0;
	if(pieceMoved == Types::Pawn && Types::GetRank(finalPosition) == promotionRank)
	{
		this->operator[](pieceMoved + offset) = Types::ClearBit(this->operator[](pieceMoved + offset), finalPosition);

		this->operator[](promotion + offset) = Types::SetBit(this->operator[](promotion + offset), finalPosition);
	}

	/* Castling Checks */
	const uint8_t oppositeColor = color == Types::White ? Types::Black : Types::White;
	bool legal = true;
	if(castling != 0)
	{
		uint8_t rookInitialPos;
		uint8_t rookFinalPos;
		switch(castling)
		{
			case Types::CastlingRights::WhiteKingSide:
				legal = !(MoveGeneration::GetAllAttacks(*this, oppositeColor) & 0x0000000000000060) && (this->CastlingRights & 0b1000);
				rookInitialPos = 7;
				rookFinalPos = 5;
				break;
			case Types::CastlingRights::WhiteQueenSide:
				legal = !(MoveGeneration::GetAllAttacks(*this, oppositeColor) & 0x000000000000000E) && (this->CastlingRights & 0b100);
				rookInitialPos = 0;
				rookFinalPos = 3;
				break;
			case Types::CastlingRights::BlackKingSide:
				legal = !(MoveGeneration::GetAllAttacks(*this, oppositeColor) & 0x6000000000000000) && (this->CastlingRights & 0b10);
				rookInitialPos = 63;
				rookFinalPos = 61;
				break;
			case Types::CastlingRights::BlackQueenSide:
				legal = !(MoveGeneration::GetAllAttacks(*this, oppositeColor) & 0xc00000000000000) && (this->CastlingRights & 0b1);
				rookInitialPos = 56;
				rookFinalPos = 59;
				break;
			default:
				throw std::invalid_argument("Invalid castling rights");
		}

		/* Move Rook */
		uint64_t rookBitboard = this->operator[](Types::Piece::Rook + offset);
		rookBitboard = Types::ClearBit(rookBitboard, rookInitialPos);
		rookBitboard = Types::SetBit(rookBitboard, rookFinalPos);
		this->operator[](Types::Piece::Rook + offset) = rookBitboard;
				
		this->CastlingRights &= ~castling; // Update Castling Rights
	}

	/* Set En Passant Square */
	this->EnPassantSquare = Types::IntToBitboard(enPassant) & 0xff0000ff0000;
	
	/* Update Turn */
	this->NextTurn();

	/* Check for Check */
	const uint64_t kingBitboard = color == Types::White ? this->WhiteKing : this->BlackKing;
/*
	uint64_t attacks = MoveGeneration::GetQueenAttacks(this->WhiteQueen, *this, oppositeColor);
	Types::PrintMove(move);
	Types::PrintBitboard(attacks);
	Types::PrintBitboard(kingBitboard & attacks);
*/
	if((kingBitboard & MoveGeneration::GetAllAttacks(*this, oppositeColor)) | !legal)
	{
		OldReverseMove(move);
		//std::cout << "FAILED" << std::endl;
		return false;
	}

	return true;
}
void GameState::OldReverseMove(const uint32_t move)
{
	const uint8_t color = (move >> 31) & 0b1;
	const uint8_t pieceMoved = (move >> 28) & 0b111;
	const uint8_t pieceCaptured = (move >> 25) & 0b111;
	const uint8_t initialPosition = (move >> 19) & 0b111111;
	const uint8_t finalPosition = (move >> 13) & 0b111111;
	const uint8_t promotion = (move >> 4) & 0b111;
	const uint8_t castling = move & 0b1111;

	const uint8_t offset = color == Types::Color::White ? 0 : 6;
	const uint8_t oppositeOffset = color == Types::Color::White ? 6 : 0;

	uint64_t bitboard = this->operator[](pieceMoved + offset);

	/* Move Piece */
	bitboard = Types::SetBit(bitboard, initialPosition);
	bitboard = Types::ClearBit(bitboard, finalPosition); 
	this->operator[](pieceMoved + offset) = bitboard;

	/* Capture Checks */
	if(pieceCaptured == Types::EnPassant && pieceMoved == Types::Pawn) 
	{
		uint64_t captureBitboard = this->operator[](Types::Pawn + oppositeOffset);
		const uint8_t pawnSquare = color == Types::White ? finalPosition - 8 : finalPosition + 8;
		captureBitboard = Types::SetBit(captureBitboard, pawnSquare);
		this->operator[](Types::Pawn + oppositeOffset) = captureBitboard;
	}
	else if(pieceCaptured != Types::None && pieceCaptured != Types::EnPassant)
	{
		uint64_t captureBitboard = this->operator[](pieceCaptured + oppositeOffset);
		captureBitboard = Types::SetBit(captureBitboard, finalPosition);
		this->operator[](pieceCaptured + oppositeOffset) = captureBitboard;
	}

	/* Promotion Checks */
	const uint8_t promotionRank = color == Types::White ? 7 : 0;
	if(pieceMoved == Types::Pawn && Types::GetRank(finalPosition) == promotionRank)
	{
		this->operator[](pieceMoved + offset) = Types::SetBit(this->operator[](pieceMoved + offset), initialPosition);

		this->operator[](promotion + offset) = Types::ClearBit(this->operator[](promotion + offset), finalPosition);
	}

	/* Castling Checks */
	if(castling != 0)
	{
		uint8_t rookInitialPos;
		uint8_t rookFinalPos;
		switch(castling)
		{
			case Types::CastlingRights::WhiteKingSide:
				rookInitialPos = 7;
				rookFinalPos = 5;
				break;
			case Types::CastlingRights::WhiteQueenSide:
				rookInitialPos = 0;
				rookFinalPos = 3;
				break;
			case Types::CastlingRights::BlackKingSide:
				rookInitialPos = 63;
				rookFinalPos = 61;
				break;
			case Types::CastlingRights::BlackQueenSide:
				rookInitialPos = 56;
				rookFinalPos = 59;
				break;
			default:
				throw std::invalid_argument("Invalid castling rights");
		}

		uint64_t rookBitboard = this->operator[](Types::Piece::Rook + offset);
		rookBitboard = Types::SetBit(rookBitboard, rookInitialPos);
		rookBitboard = Types::ClearBit(rookBitboard, rookFinalPos);
		this->operator[](Types::Piece::Rook + offset) = rookBitboard;
				
		this->CastlingRights |= castling; // Update Castling Rights
	}

	/* Remove Move from History */
	this->MoveHistory->pop_back();

	/* Add En Passant Square */
	EnPassantSquare = ((*std::prev(MoveHistory->end())) >> 7) & 0b111111;


	/* Switch Turn */
	this->PreviousTurn();
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
	const uint8_t oppositeOffset = color == Types::Color::White ? 6 : 0;

	uint64_t& pieceMovedBitboard = this->operator[](pieceMoved + offset);
	const uint8_t oppositeColor = color == Types::Color::White ? Types::Color::Black : Types::Color::White;

	bool illegalMove = false;

	/* Move Piece */
	pieceMovedBitboard = Types::SetBit(pieceMovedBitboard, finalPosition);
	pieceMovedBitboard = Types::ClearBit(pieceMovedBitboard, initialPosition);

	/* Capturing */
	if(pieceCaptured == Types::None)
	{
		//Do Nothing
	}
	else if(pieceCaptured && pieceCaptured != Types::EnPassant)
	{
		uint64_t& pieceCapturedBitboard = this->operator[](pieceCaptured + oppositeOffset);
		pieceCapturedBitboard = Types::ClearBit(pieceCapturedBitboard, finalPosition);
	}
	else if (pieceCaptured == Types::EnPassant)
	{
		uint64_t& pieceCapturedBitboard = this->operator[](Types::Pawn + oppositeOffset);
		const uint8_t pawnCapturedSquare = color == Types::White ? finalPosition - 8 : finalPosition + 8;
		pieceCapturedBitboard = Types::ClearBit(pieceCapturedBitboard, pawnCapturedSquare);
	}

	/* Promotion */
	if(promotion != Types::None)
	{
		uint64_t& piecePromotionBitboard = this->operator[](promotion + offset);
		pieceMovedBitboard = Types::ClearBit(pieceMovedBitboard, finalPosition);
		piecePromotionBitboard = Types::SetBit(piecePromotionBitboard, finalPosition);
	}

	const uint64_t allOpposingAttacks = MoveGeneration::GetAllAttacks(*this, oppositeColor); // No need to update later, as rook castling movements cannot open king up to attack

	/* Castling */
	if(castling) // King has already been moved
	{
		uint8_t rookInitialPos;
		uint8_t rookFinalPos;
		uint64_t legalMask;
		uint8_t castlingMask;

		switch (castling)
		{
			case Types::CastlingRights::WhiteKingSide:
			{
				rookInitialPos = 7;
				rookFinalPos = 5;
				legalMask = 0x30;
				castlingMask = Types::CastlingRights::WhiteKingSide;
				break;
			}
			case Types::CastlingRights::WhiteQueenSide:
			{
				rookInitialPos = 0;
				rookFinalPos = 3;
				legalMask = 0x18;
				castlingMask = Types::CastlingRights::WhiteQueenSide;
				break;
			}
			case Types::CastlingRights::BlackKingSide:
			{
				rookInitialPos = 63;
				rookFinalPos = 61;
				legalMask = 0x3000000000000000;
				castlingMask = Types::CastlingRights::BlackKingSide;
				break;
			}
			case Types::CastlingRights::BlackQueenSide:
			{
				rookInitialPos = 56;
				rookFinalPos = 59;
				legalMask = 0x1800000000000000;
				castlingMask = Types::CastlingRights::BlackQueenSide;
				break;
			}
			default:
			{
				throw std::invalid_argument("Invalid castling rights");
			}
		}

		illegalMove |= static_cast<bool>(allOpposingAttacks & legalMask);
		illegalMove |= !(this->CastlingRights & castlingMask);

		uint64_t& rookBitboard = this->operator[](Types::Piece::Rook + offset);
		rookBitboard = Types::SetBit(rookBitboard, rookFinalPos);
		rookBitboard = Types::ClearBit(rookBitboard, rookInitialPos);

		CastlingRights &= ~castlingMask; // Update Castling Rights
	}

	/* Remove and Reset En Passant Square */
	EnPassantSquare = Types::IntToBitboard(enPassant);

	/* Check for Check */
	const uint64_t& kingBitboard = this->operator[](Types::Piece::King + offset);
	illegalMove |= static_cast<bool>(kingBitboard & allOpposingAttacks);

	/* End Move */
	NextTurn();
	MoveHistory->push_back(move);

	if (illegalMove)
	{
		ReverseMove();
		return false;
	}
	return true;
}
void GameState::ReverseMove()
{
	/* Get Move */
	const uint32_t move = MoveHistory->back();
	MoveHistory->pop_back();

	const uint8_t color = (move >> 31) & 0b1;
	const uint8_t pieceMoved = (move >> 28) & 0b111;
	const uint8_t pieceCaptured = (move >> 25) & 0b111;
	const uint8_t initialPosition = (move >> 19) & 0b111111;
	const uint8_t finalPosition = (move >> 13) & 0b111111;
	const uint8_t promotion = (move >> 4) & 0b111;
	const uint8_t castling = move & 0b1111;

	const uint8_t offset = color == Types::Color::White ? 0 : 6;
	const uint8_t oppositeOffset = color == Types::Color::White ? 6 : 0;

	uint64_t& pieceMovedBitboard = this->operator[](pieceMoved + offset);

	/* Clear EnPassant */
	//EnPassant gets set when reversing capture
	EnPassantSquare = 0;

	/* Castling */
	if(castling)
	{
		uint8_t rookInitialPos;
		uint8_t rookFinalPos;
		uint8_t castlingMask;

		switch (castling)
		{
			case Types::CastlingRights::WhiteKingSide:
			{
				rookInitialPos = 7;
				rookFinalPos = 5;
				castlingMask = Types::CastlingRights::WhiteKingSide;
				break;
			}
			case Types::CastlingRights::WhiteQueenSide:
			{
				rookInitialPos = 0;
				rookFinalPos = 3;
				castlingMask = Types::CastlingRights::WhiteQueenSide;
				break;
			}
			case Types::CastlingRights::BlackKingSide:
			{
				rookInitialPos = 63;
				rookFinalPos = 61;
				castlingMask = Types::CastlingRights::BlackKingSide;
				break;
			}
			case Types::CastlingRights::BlackQueenSide:
			{
				rookInitialPos = 56;
				rookFinalPos = 59;
				castlingMask = Types::CastlingRights::BlackQueenSide;
				break;
			}
			default:
			{
				throw std::invalid_argument("Invalid castling rights for Reverse??");
			}
		}

		uint64_t& rookBitboard = this->operator[](Types::Piece::Rook + offset);
		rookBitboard = Types::ClearBit(rookBitboard, rookFinalPos);
		rookBitboard = Types::SetBit(rookBitboard, rookInitialPos);

		CastlingRights |= castlingMask; // Update Castling Rights
	}

	/* Promotion */
	if(promotion != Types::None)
	{
		uint64_t& piecePromotionBitboard = this->operator[](promotion + offset);
		pieceMovedBitboard = Types::SetBit(pieceMovedBitboard, finalPosition);
		piecePromotionBitboard = Types::ClearBit(piecePromotionBitboard, finalPosition);
	}

	/* Capture */
	if(pieceCaptured == Types::None)
	{
		//Do Nothing
	}
	else if(pieceCaptured && pieceCaptured != Types::EnPassant)
	{
		uint64_t& pieceCapturedBitboard = this->operator[](pieceCaptured + oppositeOffset);
		pieceCapturedBitboard = Types::SetBit(pieceCapturedBitboard, finalPosition);
	}
	else if (pieceCaptured == Types::EnPassant)
	{
		uint64_t& pieceCapturedBitboard = this->operator[](Types::Pawn + oppositeOffset);
		const uint8_t pawnCapturedSquare = color == Types::White ? finalPosition - 8 : finalPosition + 8;
		pieceCapturedBitboard = Types::SetBit(pieceCapturedBitboard, pawnCapturedSquare);

		EnPassantSquare = Types::IntToBitboard(finalPosition);// Set EnPassant
	}

	/* Piece Move */
	pieceMovedBitboard = Types::ClearBit(pieceMovedBitboard, finalPosition);
	pieceMovedBitboard = Types::SetBit(pieceMovedBitboard, initialPosition);

	/* End Move */
	PreviousTurn();
}


void GameState::NextTurn()
{
	this->SideToMove = this->SideToMove == Types::White ? Types::Black : Types::White;
}


void GameState::PreviousTurn()
{
	this->SideToMove = this->SideToMove == Types::White ? Types::Black : Types::White;
}


