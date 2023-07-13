#include "Piece.h"

Piece::Piece():m_type(EPieceType::None), m_color(EColor::None)
{
}

EPieceType Piece::GetType() const
{
	return this->m_type;
}

EColor Piece::GetColor() const
{
	return this->m_color;
}


bool Piece::IsMoveRegular(Position p1, Position p2)
{
	return true;
}

PositionList Piece::DeterminePattern(Position p1, Position p2)
{
	return {};
}

Piece::Piece(EPieceType type, EColor color)
{
	this->m_type = type;
	this->m_color = color;
}