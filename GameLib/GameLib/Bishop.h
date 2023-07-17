#pragma once
#include "Piece.h"

class Bishop:public Piece
{
public:
    // Constructor
    Bishop(EColor);
    
    // Other methods
    bool IsMoveRegular(Position p1, Position p2) override;
    PositionList DeterminePattern(Position p1, Position p2) override;
    PositionMatrix AllMoves(Position p) override;
};

