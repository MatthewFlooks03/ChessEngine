#include "movegeneration.h"
#include "tables.h"

std::list<uint32_t> MoveGeneration::GetAllPseudoMoves(const GameState& gameState)
{
	std::list<uint32_t> moves;
	for (uint8_t i = Types::King; i <= Types::Pawn; i++)
		GetPseudoMoves(gameState, i, &moves);
	return moves;
}

void MoveGeneration::GetPseudoMoves(const GameState& gameState, const uint8_t piece, std::list<uint32_t>* moves)
{
	uint64_t bitboard;
	uint64_t (*getFunction) (const uint8_t, const GameState&) = nullptr;

	switch (piece)
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

	std::list<uint8_t> locations = Types::SerialiseBitboard(bitboard);

	for(auto iterator = locations.begin(); iterator != locations.end(); ++iterator)
	{
		const uint8_t location = *iterator;

		const uint64_t movesBitboard = getFunction(location, gameState);

		std::list<uint8_t> movesList = Types::SerialiseBitboard(movesBitboard);

		for(auto it = movesList.begin(); it != movesList.end(); ++it)
		{
			uint32_t move = 0;

			const uint8_t capture = gameState.GetPiece(*it, 1 ^ gameState.SideToMove);

			uint8_t castling = 0;

			if(piece == Types::King)
			{
				if (std::abs(static_cast<int>(location - move)) == 2)
				{
					castling = gameState.SideToMove == Types::Color::White ? Types::WhiteKingSide : Types::BlackKingSide;
				}
				else
				{
					castling = gameState.SideToMove == Types::Color::White ? Types::WhiteQueenSide : Types::BlackQueenSide;
				}
			}

			move |= gameState.SideToMove << 22;
			move |= piece << 19;
			move |= capture << 16;
			move |= castling << 12;
			move |= location << 6;
			move |= *it;

			moves->push_back(move);
		}
	}
}

uint64_t MoveGeneration::GetAllAttacks(const GameState& gameState, const uint8_t color)
{
	uint64_t bitboard = 0;

	bitboard |= GetKingAttacks(color == Types::Color::White ? gameState.WhiteKing : gameState.BlackKing);
	bitboard |= GetQueenAttacks(color == Types::Color::White ? gameState.WhiteQueen : gameState.BlackQueen);
	bitboard |= GetRookAttacks(color == Types::Color::White ? gameState.WhiteRook : gameState.BlackRook);
	bitboard |= GetBishopAttacks(color == Types::Color::White ? gameState.WhiteBishop : gameState.BlackBishop);
	bitboard |= GetKnightAttacks(color == Types::Color::White ? gameState.WhiteKnight : gameState.BlackKnight);
	bitboard |= GetPawnAttacks(color == Types::Color::White ? gameState.WhitePawn : gameState.BlackPawn, color);

	return bitboard;
}

uint64_t MoveGeneration::GetKingAttacks(const uint64_t bitboard)
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

uint64_t MoveGeneration::GetQueenAttacks(const uint64_t bitboard)
{
	uint64_t attacks = GetRookAttacks(bitboard);
	attacks |= GetBishopAttacks(bitboard);
	return attacks;
}

uint64_t MoveGeneration::GetRookAttacks(const uint64_t bitboard)
{
	std::list<uint8_t> locations = Types::SerialiseBitboard(bitboard);
	uint64_t attacks = 0;
	for(auto i = locations.begin(); i != locations.end(); ++i)
	{
		attacks |= GetRookAttacks(*i);
	}
	return attacks;
}

uint64_t  MoveGeneration::GetBishopAttacks(const uint64_t bitboard)
{
	std::list<uint8_t> locations = Types::SerialiseBitboard(bitboard);
	uint64_t attacks = 0;
	for(auto i = locations.begin(); i != locations.end(); ++i)
	{
		attacks |= GetBishopAttacks(*i);
	}
	return attacks;
}

uint64_t MoveGeneration::GetKnightAttacks(const uint64_t bitboard)
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

