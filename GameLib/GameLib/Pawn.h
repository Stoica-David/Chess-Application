#pragma once
#include "Piece.h"

class Pawn:public Piece
{
public:
    //Constructor
    Pawn(EColor);

    // Other methods
    bool IsMoveRegular(Position p1, Position p2) const override;
    PositionList DeterminePattern(Position p1, Position p2) const override;
    PositionMatrix AllMoves(Position p) const override;
};

