#pragma once
#include "Piece.h"

class Rook:public Piece
{
public:
	// Constructor
	Rook(EColor);
	
	bool IsMoveRegular(int x_curr, int y_curr, int x_next, int y_next) override;
};