#pragma once
#include "Piece.h"

class Rook : public Piece
{
public:
	// Constructor
	Rook(EColor);
	
	// Piece methods
	bool IsMoveRegular(Position p1, Position p2) const override;

	PositionList DeterminePattern(Position p1, Position p2) const override;
	
	PositionMatrix AllMoves(Position p) const override;

	// Other methods
	static bool RookMove(Position p1, Position p2)
	{
		auto x1 = p1.x,
			x2 = p2.x,
			y1 = p1.y,
			y2 = p2.y;

		return ((x1 == x2) ^ (y1 == y2));
	}
};