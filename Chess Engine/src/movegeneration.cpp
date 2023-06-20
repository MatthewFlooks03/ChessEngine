#include "movegeneration.h"
#include "tables.h"

std::list<uint32_t> MoveGeneration::GenerateAllPseudoMoves(const GameState& gameState)
{
	std::list<uint32_t> moves;
	for (uint8_t i = Types::King; i <= Types::Pawn; i++)
		GeneratePseudoMoves(gameState, i, &moves);
	return moves;
}

void MoveGeneration::GeneratePseudoMoves(const GameState& gameState, const uint8_t piece, std::list<uint32_t>* moves)
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
