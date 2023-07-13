#pragma once

#include "Piece.h"

class Knight :public Piece
{
public:
	// Constructor
	Knight(EColor);
	
	bool IsMoveRegular(Position p1, Position p2) override;
};

