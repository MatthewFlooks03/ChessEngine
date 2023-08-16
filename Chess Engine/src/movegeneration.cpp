#include "movegeneration.h"
#include "tables.h"

std::vector<uint32_t> MoveGeneration::GetAllPseudoMoves(const GameState& gameState)
{
	std::vector<uint32_t> moves;
	for (uint8_t i = Types::King; i <= Types::Pawn; i++)
		GetPseudoMoves(gameState, i, &moves);
	return moves;
}
void MoveGeneration::GetPseudoMoves(const GameState& gameState, const uint8_t pieceMoved,std::vector<uint32_t>* moves)
{
	uint64_t bitboard;
	uint64_t (*getFunction) (const uint8_t, const GameState&, const uint8_t);

	switch (pieceMoved)
	{
		case Types::Piece::Pawn:
		{
			bitboard = gameState.SideToMove == Types::Color::White ? gameState.WhitePawn : gameState.BlackPawn;
			getFunction = gameState.SideToMove == Types::Color::White ? Tables::GetWhitePawnMoves : Tables::GetBlackPawnMoves;
			break;
		}
		case Types::Piece::Knight:
		{
			bitboard = gameState.SideToMove == Types::Color::White ? gameState.WhiteKnight : gameState.BlackKnight;
			getFunction = Tables::GetKnightMoves;
			break;
		}
		case Types::Piece::Bishop:
		{
			bitboard = gameState.SideToMove == Types::Color::White ? gameState.WhiteBishop : gameState.BlackBishop;
			getFunction = Tables::GetBishopMoves;
			break;
		}
		case Types::Piece::Rook:
		{
			bitboard = gameState.SideToMove == Types::Color::White ? gameState.WhiteRook : gameState.BlackRook;
			getFunction = Tables::GetRookMoves;
			break;
		}
		case Types::Piece::Queen:
		{
			bitboard = gameState.SideToMove == Types::Color::White ? gameState.WhiteQueen : gameState.BlackQueen;
			getFunction = Tables::GetQueenMoves;
			break;
		}
		case Types::Piece::King:
		{
			bitboard = gameState.SideToMove == Types::Color::White ? gameState.WhiteKing : gameState.BlackKing;
			getFunction = Tables::GetKingMoves;
			break;
		}
		default:
		{
			throw std::invalid_argument("Invalid piece");
		}
	}

	const uint8_t color = gameState.SideToMove; // COLOR

	const std::vector<uint8_t> locations = Types::SerialiseBitboard(bitboard);

	for (const unsigned char initialPosition : locations)
	{
		// INITIAL POSITION

		const uint64_t movesBitboard = getFunction(initialPosition, gameState, color);

		std::vector<uint8_t> movesList = Types::SerialiseBitboard(movesBitboard);

		for (const unsigned char& it : movesList)
		{
			const uint8_t finalPosition = it; // FINAL POSITION
			const uint8_t pieceCaptured = gameState.GetPiece(it, 1 ^ gameState.SideToMove); // CAPTURED PIECE

			uint8_t castling = 0; // CASTLING
			if (pieceMoved == Types::King)
			{
				if (static_cast<int>(initialPosition - finalPosition) == -2)
				{
					castling = gameState.SideToMove == Types::Color::White ? Types::WhiteKingSide : Types::BlackKingSide;
				}
				else if (static_cast<int>(initialPosition - finalPosition) == 2)
				{
					castling = gameState.SideToMove == Types::Color::White ? Types::WhiteQueenSide : Types::BlackQueenSide;
				}
			}

			uint8_t enPassant = 0; // EN PASSANT
			if (pieceMoved == Types::Pawn && std::abs(static_cast<int>(initialPosition - finalPosition)) == 16)
			{
				enPassant = gameState.SideToMove == Types::Color::White ? initialPosition + 8 : initialPosition - 8;
			}

			uint32_t move = 0;

			uint8_t promotion = Types::None; // PROMOTION

			if (pieceMoved == Types::Pawn &&
				(
				color == Types::White && finalPosition <=63 && finalPosition >= 56
				||
				color == Types::Black && finalPosition <= 7
				))
			{
				for(uint8_t i = Types::Queen; i <= Types::Knight; i++)
				{
					move = 0;
					promotion = i;

					move |= color << 31;
					move |= pieceMoved << 28;
					move |= pieceCaptured << 25;
					move |= initialPosition << 19;
					move |= finalPosition << 13;
					move |= enPassant << 7;
					move |= promotion << 4;
					move |= castling;
					moves->push_back(move);
				}
			}
			else
			{
				move = 0;
				move |= color << 31;
				move |= pieceMoved << 28;
				move |= pieceCaptured << 25;
				move |= initialPosition << 19;
				move |= finalPosition << 13;
				move |= enPassant << 7;
				move |= promotion << 4;
				move |= castling;

				moves->push_back(move);
			}

		}
	}
}

uint64_t MoveGeneration::GetAllAttacks(const GameState& gameState, const uint8_t color)
{
	uint64_t bitboard = 0;

	bitboard |= GetKingAttacks(color == Types::Color::White ? gameState.WhiteKing : gameState.BlackKing, color);
	bitboard |= GetQueenAttacks(color == Types::Color::White ? gameState.WhiteQueen : gameState.BlackQueen, gameState, color);
	bitboard |= GetRookAttacks(color == Types::Color::White ? gameState.WhiteRook : gameState.BlackRook, gameState, color);
	bitboard |= GetBishopAttacks(color == Types::Color::White ? gameState.WhiteBishop : gameState.BlackBishop, gameState, color);
	bitboard |= GetKnightAttacks(color == Types::Color::White ? gameState.WhiteKnight : gameState.BlackKnight, color);
	bitboard |= GetPawnAttacks(color == Types::Color::White ? gameState.WhitePawn : gameState.BlackPawn, color);

	return bitboard;
}
uint64_t MoveGeneration::GetKingAttacks(const uint64_t bitboard, uint8_t color)
{
	using namespace Types;
	uint64_t attacks = North(bitboard);
	attacks |= South(bitboard);
	attacks |= East(bitboard);
	attacks |= West(bitboard);
	attacks |= NorthEast(bitboard);
	attacks |= NorthWest(bitboard);
	attacks |= SouthEast(bitboard);
	attacks |= SouthWest(bitboard);

	return attacks;
}
uint64_t MoveGeneration::GetQueenAttacks(const uint64_t bitboard, const GameState& gameState, uint8_t color)
{
	uint64_t attacks = GetRookAttacks(bitboard, gameState, color);
	attacks |= GetBishopAttacks(bitboard, gameState, color);
	return attacks;
}
uint64_t MoveGeneration::GetRookAttacks(const uint64_t bitboard, const GameState& gameState, uint8_t color)
{
	const std::vector<uint8_t> locations = Types::SerialiseBitboard(bitboard);
	uint64_t attacks = 0;
	for (unsigned const char& location : locations)
	{
		attacks |= Tables::GetRookMoves(location, gameState, color);
	}
	return attacks;
}
uint64_t  MoveGeneration::GetBishopAttacks(const uint64_t bitboard, const GameState& gameState, uint8_t color)
{
	const std::vector<uint8_t> locations = Types::SerialiseBitboard(bitboard);
	uint64_t attacks = 0;
	for (unsigned const char& location : locations)
	{
		attacks |= Tables::GetBishopMoves(location, gameState, color);
	}
	return attacks;
}
uint64_t MoveGeneration::GetKnightAttacks(const uint64_t bitboard, uint8_t color)
{
	using namespace Types;
	uint64_t attacks = NorthEast(North(bitboard));
	attacks |= NorthWest(North(bitboard));
	attacks |= SouthEast(South(bitboard));
	attacks |= SouthWest(South(bitboard));
	attacks |= NorthEast(East(bitboard));
	attacks |= NorthWest(West(bitboard));
	attacks |= SouthEast(East(bitboard));
	attacks |= SouthWest(West(bitboard));

	return attacks;
}
uint64_t MoveGeneration::GetPawnAttacks(const uint64_t bitboard, uint8_t color)
{
	using namespace Types;
	uint64_t attacks;
	if(color == White)
	{
		attacks = NorthEast(bitboard);
		attacks |= NorthWest(bitboard);
	}
	else
	{
		attacks = SouthEast(bitboard);
		attacks |= SouthWest(bitboard);
	}

	return attacks;
}
