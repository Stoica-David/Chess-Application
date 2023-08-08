#pragma once
#include "Piece.h"

class King : public Piece
{
public:
    // Constructor
    King(EColor);

    // Piece methods
    bool IsMoveRegular(Position p1, Position p2) const override;

    PositionList DeterminePattern(Position p1, Position p2) const override;

    PositionMatrix AllMoves(Position p) const override;

private:
    //Other methods
    static bool Horizontal(Position p1, Position p2)
	{
		int x1 = p1.x,
			y1 = p1.y,
			x2 = p2.x,
			y2 = p2.y;

		return (AbsValue(x2, x1) == 0 && AbsValue(y2, y1) == 1);
	}

    static bool Vertical(Position p1, Position p2)
	{
		int x1 = p1.x,
			y1 = p1.y,
			x2 = p2.x,
			y2 = p2.y;


		return (AbsValue(x2, x1) == 1 && AbsValue(y2, y1) == 0);
	}

    static bool Diagonal(Position p1, Position p2)
	{
		int x1 = p1.x,
			y1 = p1.y,
			x2 = p2.x,
			y2 = p2.y;

		return (AbsValue(x2, x1) == 1 && AbsValue(y2, y1) == 1);
	}

	static bool CastleMove(Position p1, Position p2)
	{
		int x1 = p1.x,
			y1 = p1.y,
			x2 = p2.x,
			y2 = p2.y;

		return (AbsValue(y2, y1) == 2);
	}
};

