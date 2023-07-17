#pragma once

#include "Piece.h"

class Knight :public Piece
{
public:
	// Constructor
	Knight(EColor);
	
	// Other methods
	bool IsMoveRegular(Position p1, Position p2) const override;
	PositionList DeterminePattern(Position p1, Position p2) const override;
	PositionMatrix AllMoves(Position p) const override;
};

