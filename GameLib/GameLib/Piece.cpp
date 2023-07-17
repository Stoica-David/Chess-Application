#include "Piece.h"

EPieceType Piece::GetType() const
{
	return m_type;
}

EColor Piece::GetColor() const
{
	return m_color;
}

bool Piece::IsMoveRegular(Position p1, Position p2)
{
	return true;
}

PositionList Piece::DeterminePattern(Position p1, Position p2)
{
	return {};
}

PositionList Piece::AllMoves(Position p)
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

Piece::Piece(EPieceType type, EColor color)
{
	m_type = type;
	m_color = color;
}