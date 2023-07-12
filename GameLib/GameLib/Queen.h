#pragma once
#include "Piece.h"

class Queen:public Piece
{
public:
    // Constructor
    Queen(EColor);

    bool IsMoveRegular(int x_curr, int y_curr, int x_next, int y_next);
};

