#pragma once
#include "Piece.h"

class Queen:public Piece
{
public:
    // Constructor
    Queen(EColor);

    // Other methods
    bool IsMoveRegular(Position p1, Position p2);
    PositionList DeterminePattern(Position p1, Position p2) override;
};

