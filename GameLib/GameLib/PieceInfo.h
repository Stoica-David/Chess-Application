#pragma once
#include "IPieceInfo.h"

class PieceInfo:public IPieceInfo
{
public:
	// Constructor
	PieceInfo(EPieceType type, EColor color)
		:m_type(type),
		m_color(color)
	{
	}

	// IPieceInfo methods
	EPieceType GetType()const override;
	EColor GetColor()const override;

protected:
	EPieceType m_type;
	EColor m_color;
};

