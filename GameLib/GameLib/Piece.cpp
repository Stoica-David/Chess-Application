#include "Piece.h"

#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"
#include "Pawn.h"

Piece::Piece(EPieceType type, EColor color)
{
	m_type = type;
	m_color = color;
}

PiecesPtr Piece::Produce(EPieceType type, EColor color)
{
	switch (type)
	{
	case EPieceType::Rook:
		return std::make_shared<Rook>(color); 
	case EPieceType::Knight:
		return std::make_shared<Knight>(color); 
	case EPieceType::Bishop:
		return std::make_shared<Bishop>(color); 
	case EPieceType::Queen:
		return std::make_shared<Queen>(color); 
	case EPieceType::King:
		return std::make_shared<King>(color); 
	case EPieceType::Pawn:
		return std::make_shared<Pawn>(color); 
	}
	return {};
}

EPieceType Piece::GetType() const
{
	return m_type;
}

EColor Piece::GetColor() const
{
	return m_color;
}

bool Piece::IsMoveRegular(Position p1, Position p2) const
{
	return true;
}

PositionList Piece::DeterminePattern(Position p1, Position p2) const
{
	return {};
}

PositionMatrix Piece::AllMoves(Position p) const
{
	return {};
}

bool Piece::IsWhite() const
{
	return (m_color == EColor::White);
}

int Piece::AbsValue(int x, int y) const
{
	return (std::abs(x - y));
}

bool Piece::IsBlack() const
{
	return (m_color == EColor::Black);
}