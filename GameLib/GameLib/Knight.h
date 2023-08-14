#pragma once

#include "Piece.h"

class Knight : public Piece
{
public:
	// Constructor
	Knight(EColor);
	
	// Piece methods
	bool IsMoveRegular(Position p1, Position p2) const override;

	PositionList DeterminePattern(Position p1, Position p2) const override;

	PositionMatrix AllMoves(Position p) const override;

private:
	// Other methods
	static bool VertL(Position p1, Position p2);
	static bool HorizontL(Position p1, Position p2);
};

