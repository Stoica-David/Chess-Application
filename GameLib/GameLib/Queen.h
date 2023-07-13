#pragma once
#include "Piece.h"

class Queen:public Piece
{
public:
    // Constructor
    Queen(EColor);

    bool IsMoveRegular(Position p1, Position p2);
};

