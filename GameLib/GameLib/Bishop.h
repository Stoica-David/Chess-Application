#pragma once
#include "Piece.h"

class Bishop:public Piece
{
public:
    // Constructor
    Bishop(EColor);
    
    bool IsMoveRegular(int x_curr, int y_curr, int x_next, int y_next) override;
};

