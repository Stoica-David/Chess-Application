#pragma once
#include "Piece.h"

class King:public Piece
{
public:
    // Constructor
    King(EColor);

    // Other methods
    bool IsMoveRegular(Position p1, Position p2);
    PositionList DeterminePattern(Position p1, Position p2) override;
    PositionMatrix AllMoves(Position p) override;
};

