#pragma once
#include "Piece.h"

class Bishop:public Piece
{
public:
    bool IsMoveRegular(int x_curr, int y_curr, int x_next, int y_next) override;
    Bishop(EColor);
};

