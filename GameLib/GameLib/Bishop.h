#pragma once
#include "Piece.h"

class Bishop:public Piece
{
public:
    // Constructor
    Bishop(EColor);
    
    bool IsMoveRegular(Position p1, Position p2) override;
};

