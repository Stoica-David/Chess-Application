#include "Piece.h"

Piece::Piece():m_type(EPieceType::None), m_color(EColor::none)
{
}

EPieceType Piece::GetType() const
{
	return m_type;
}

Piece::Piece(EPieceType type, EColor color)
{
	this->m_type = type;
	this->m_color = color;
}