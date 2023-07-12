#include "Piece.h"

Piece::Piece():m_type(EPieceType::None), m_color(EColor::none)
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

bool Piece::IsMoveRegular(int x_curr, int y_curr, int x_next, int y_next)
{
	return true;
}

Piece::Piece(EPieceType type, EColor color)
{
	this->m_type = type;
	this->m_color = color;
}