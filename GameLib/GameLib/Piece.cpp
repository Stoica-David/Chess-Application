#include "Piece.h"

Piece::Piece(EPieceType type, EColor color)
{
	m_type = type;
	m_color = color;
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