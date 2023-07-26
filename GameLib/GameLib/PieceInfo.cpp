#include "PieceInfo.h"

#include <memory>

PieceInfo::PieceInfo(EPieceType type, EColor color) 
	: m_type(type)
	, m_color(color)
{
}

EPieceType PieceInfo::GetType() const
{
	return m_type;
}

EColor PieceInfo::GetColor() const
{
	return m_color;
}
