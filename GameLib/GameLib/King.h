#pragma once
#include "Piece.h"

class King:public Piece
{
public:
    // Constructor
    King(EColor);

    // Other methods
    bool IsMoveRegular(Position p1, Position p2);
};

