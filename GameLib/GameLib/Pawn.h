#pragma once
#include "Piece.h"

class Pawn:public Piece
{
public:
    //Constructor
    Pawn(EColor);

    bool IsMoveRegular(Position p1, Position p2) override;
};

