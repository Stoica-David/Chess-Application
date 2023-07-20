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
};