#include "King.h"

King::King(EColor color) : Piece(EPieceType::King, color)
{
}

bool King::IsMoveRegular(Position p1, Position p2) const
{
	return (Horizontal(p1, p2) || Vertical(p1, p2) || Diagonal(p1, p2));
}

PositionList King::DeterminePattern(Position p1, Position p2) const
{
	PositionList newPattern = { p2 };

	return newPattern;
}

PositionMatrix King::AllMoves(Position p) const
{
	PositionMatrix newMatrix;

	int x = p.x,
		y = p.y;

	Position upLeft =	 { x - 1, y - 1 },
			 up =		 { x - 1, y     },
			 upRight =	 { x - 1, y + 1 },
			 left =		 { x,     y - 1 },
			 right =	 { x,     y + 1 },
			 downLeft =  { x + 1, y - 1 },
			 down =		 { x + 1, y     },
			 downRight = { x + 1, y + 1 };

	newMatrix.resize(8);

	if (IsInTable(upLeft))
	{
		newMatrix[0].push_back(upLeft);
	}
	
	if (IsInTable(up))
	{
		newMatrix[1].push_back(up);
	}

	if (IsInTable(upRight))
	{
		newMatrix[2].push_back(upRight);
	}

	if (IsInTable(left))
	{
		newMatrix[3].push_back(left);
	}

    if (IsInTable(right))
	{
		newMatrix[4].push_back(right);
	}

	if (IsInTable(downLeft))
	{
		newMatrix[5].push_back(downLeft);
	}
	
	if (IsInTable(down))
	{
		newMatrix[6].push_back(down);
	}
	
	if (IsInTable(downRight))
	{
		newMatrix[7].push_back(downRight);
	}

	return newMatrix;
}

bool King::Horizontal(Position p1, Position p2)
{
	int x1 = p1.x,
		y1 = p1.y,
		x2 = p2.x,
		y2 = p2.y;

	return (AbsValue(x2, x1) == 0 && AbsValue(y2, y1) == 1);
}

bool King::Vertical(Position p1, Position p2)
{
	int x1 = p1.x,
		y1 = p1.y,
		x2 = p2.x,
		y2 = p2.y;


	return (AbsValue(x2, x1) == 1 && AbsValue(y2, y1) == 0);
}

bool King::Diagonal(Position p1, Position p2)
{
	int x1 = p1.x,
		y1 = p1.y,
		x2 = p2.x,
		y2 = p2.y;

	return (AbsValue(x2, x1) == 1 && AbsValue(y2, y1) == 1);
}

bool King::CastleMove(Position p1, Position p2)
{
	int x1 = p1.x,
		y1 = p1.y,
		x2 = p2.x,
		y2 = p2.y;

	return (AbsValue(y2, y1) == 2);
}
