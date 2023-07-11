#include "Piece.h"

Piece::Piece():m_type(EPieceType::None), color(EColor::none)
{
}

EPieceType Piece::GetType() const
{
	return m_type;
}

Piece::Piece(EPieceType type, EColor color)
{
	this->m_type = type;
	this->color = color;
}