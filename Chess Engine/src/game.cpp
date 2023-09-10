#pragma once
#include "game.h"

#include "movegeneration.h"


Game::Game()
{
	CurrentState = new GameState();
}

Game::Game(const std::string& fen)
{
	CurrentState = new GameState(fen);
}

bool Game::ExecuteMove(const uint32_t move)
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

	uint64_t& pieceMovedBitboard = CurrentState->operator[](pieceMoved + offset);
	const uint8_t oppositeColor = color == Types::Color::White ? Types::Color::Black : Types::Color::White;

	bool illegalMove = false;

	/* Move Piece */
	pieceMovedBitboard = Types::SetBit(pieceMovedBitboard, finalPosition);
	pieceMovedBitboard = Types::ClearBit(pieceMovedBitboard, initialPosition);

	/* Capturing */
	if (pieceCaptured == Types::None)
	{
		//Do Nothing
	}
	else if (pieceCaptured && pieceCaptured != Types::EnPassant)
	{
		uint64_t& pieceCapturedBitboard = CurrentState->operator[](pieceCaptured + oppositeOffset);
		pieceCapturedBitboard = Types::ClearBit(pieceCapturedBitboard, finalPosition);
	}
	else if (pieceCaptured == Types::EnPassant && pieceMoved == Types::Pawn)
	{
		uint64_t& pieceCapturedBitboard = CurrentState->operator[](Types::Pawn + oppositeOffset);
		const uint8_t pawnCapturedSquare = color == Types::White ? finalPosition - 8 : finalPosition + 8;
		pieceCapturedBitboard = Types::ClearBit(pieceCapturedBitboard, pawnCapturedSquare);
	}

	/* Promotion */
	if (promotion != Types::None)
	{
		uint64_t& piecePromotionBitboard = CurrentState->operator[](promotion + offset);
		pieceMovedBitboard = Types::ClearBit(pieceMovedBitboard, finalPosition);
		piecePromotionBitboard = Types::SetBit(piecePromotionBitboard, finalPosition);
	}

	const uint64_t allOpposingAttacks = MoveGeneration::GetAllAttacks(*CurrentState, oppositeColor); // No need to update later, as rook castling movements cannot open king up to attack

	/* Castling */
	if (castling) // King has already been moved
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
		illegalMove |= !(CurrentState->CastlingRights & castlingMask);
		if (!(Types::IntToBitboard(rookInitialPos) & CurrentState->operator[](Types::Piece::Rook + offset)))
		{
			illegalMove = true;
		}
		else
		{
			uint64_t& rookBitboard = CurrentState->operator[](Types::Piece::Rook + offset);
			rookBitboard = Types::SetBit(rookBitboard, rookFinalPos);
			rookBitboard = Types::ClearBit(rookBitboard, rookInitialPos);
		}


		CurrentState->CastlingRights &= ~castlingMask; // Update Castling Rights
	}

	/* Castling Rights Removal */
	if (pieceMoved == Types::King && !castling)
	{
		CurrentState->CastlingRights = 0;
	}
	if (pieceMoved == Types::Rook)
	{
		switch (initialPosition)
		{
		case 0:
		{
			CurrentState->CastlingRights &= ~Types::CastlingRights::WhiteQueenSide;
			break;
		}
		case 7:
		{
			CurrentState->CastlingRights &= ~Types::CastlingRights::WhiteKingSide;
			break;
		}
		case 56:
		{
			CurrentState->CastlingRights &= ~Types::CastlingRights::BlackQueenSide;
			break;
		}
		case 63:
		{
			CurrentState->CastlingRights &= ~Types::CastlingRights::BlackKingSide;
			break;
		}
		default:
		{
			break;
		}
		}
	}

	/* Remove and Reset En Passant Square */
	if (enPassant == 0)
	{
		CurrentState->EnPassantSquare = 0;
	}
	else
	{
		CurrentState->EnPassantSquare = Types::IntToBitboard(enPassant);
	}

	/* Check for Check */
	const uint64_t& kingBitboard = CurrentState->operator[](Types::Piece::King + offset);
	illegalMove |= static_cast<bool>(kingBitboard & allOpposingAttacks);

	/* End Move */
	NextTurn();

	if (illegalMove)
	{
		ReverseMove();
		return false;
	}
	return true;
}
void Game::ReverseMove()
{
	CurrentState = CurrentState->PreviousState;
	delete CurrentState->NextState;
	CurrentState->NextState = nullptr;

}

{

	/* Get Move */
	const uint32_t move = MoveHistory->back();
	
	
	MoveHistory->pop_back();
	const uint32_t prevMove = MoveHistory->back();

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

	/* Remove and Reset En Passant Square */
	EnPassantSquare = 0;
	if (const uint8_t prevEnPassant = (prevMove >> 7) & 0b111111; prevEnPassant != 0)
	{
		EnPassantSquare = Types::IntToBitboard(prevEnPassant);
	}

	/* Castling */
	if (castling)
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
		if ((Types::IntToBitboard(rookFinalPos) & this->operator[](Types::Piece::Rook + offset)))
		{
			rookBitboard = Types::SetBit(rookBitboard, rookInitialPos);
			rookBitboard = Types::ClearBit(rookBitboard, rookFinalPos);
		}

		CastlingRights |= castlingMask; // Update Castling Rights
	}

	/* Promotion */
	if (promotion != Types::None)
	{
		uint64_t& piecePromotionBitboard = this->operator[](promotion + offset);
		pieceMovedBitboard = Types::SetBit(pieceMovedBitboard, finalPosition);
		piecePromotionBitboard = Types::ClearBit(piecePromotionBitboard, finalPosition);
	}

	/* Capture */
	if (pieceCaptured == Types::None)
	{
		//Do Nothing
	}
	else if (pieceCaptured && pieceCaptured != Types::EnPassant)
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
}



