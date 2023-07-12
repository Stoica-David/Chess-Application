#pragma once

#include "Piece.h"

class Knight :public Piece
{
public:
	// Constructor
	Knight(EColor);
	
	bool IsMoveRegular(int x_curr, int y_curr, int x_next, int y_next) override;
};

