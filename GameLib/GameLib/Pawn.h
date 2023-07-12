#pragma once
#include "Piece.h"

class Pawn:public Piece
{
public:
    //Constructor
    Pawn(EColor);

    bool IsMoveRegular(int x_curr, int y_curr, int x_next, int y_next) override;
};

