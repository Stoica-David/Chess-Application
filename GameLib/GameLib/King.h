#pragma once
#include "Piece.h"

class King:public Piece
{
public:
    // Constructor
    King(EColor);

    // Other methods
    bool IsMoveRegular(int x_curr, int y_curr, int x_next, int y_next);
};

