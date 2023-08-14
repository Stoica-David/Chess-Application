#pragma once
#include "Piece.h"

class King : public Piece
{
public:
    // Constructor
    King(EColor);

    // Piece methods
    bool IsMoveRegular(Position p1, Position p2) const override;

    PositionList DeterminePattern(Position p1, Position p2) const override;

    PositionMatrix AllMoves(Position p) const override;

private:
    //Other methods
    static bool Horizontal(Position p1, Position p2);
    static bool Vertical(Position p1, Position p2);
    static bool Diagonal(Position p1, Position p2);
	static bool CastleMove(Position p1, Position p2);
};

