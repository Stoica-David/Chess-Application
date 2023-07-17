#pragma once

#include "Piece.h"

class Knight :public Piece
{
public:
	// Constructor
	Knight(EColor);
	
	// Other methods
	bool IsMoveRegular(Position p1, Position p2) override;
	PositionList DeterminePattern(Position p1, Position p2) override;
	PositionList AllMoves(Position p) override;
};

