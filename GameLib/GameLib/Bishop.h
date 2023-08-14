#pragma once
#include "Piece.h"

class Bishop : public Piece
{
public:
    // Constructor
    Bishop(EColor);
    
    // Piece methods
    bool IsMoveRegular(Position p1, Position p2) const override;

    PositionList DeterminePattern(Position p1, Position p2) const override;

    PositionMatrix AllMoves(Position p) const override;

	// Other methods
	static bool BishopMove(Position p1, Position p2);
};

