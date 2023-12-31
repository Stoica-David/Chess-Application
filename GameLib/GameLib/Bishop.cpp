#include "Bishop.h"

Bishop::Bishop(EColor color) : Piece(EPieceType::Bishop, color)
{
}

bool Bishop::IsMoveRegular(Position p1, Position p2) const
{
	return (BishopMove(p1, p2));
}


PositionList Bishop::DeterminePattern(Position p1, Position p2) const
{
	PositionList newPosition;

	int x1 = p1.x,
		y1 = p1.y,
		x2 = p2.x,
		y2 = p2.y;

	if (x1 > x2)
	{
		if (y2 > y1)
		{
			while (x1 > x2 && y1 < y2)
			{
				x1--;
				y1++;

				newPosition.push_back({ x1, y1 });
			}
		}
		else
		{
			while (x1 > x2 && y1 > y2)
			{
				x1--;
				y1--;

				newPosition.push_back({ x1, y1 });
			}
		}
	}
	else
	{
		if (y2 > y1)
		{
			while (x1 < x2 && y1 < y2)
			{
				x1++;
				y1++;

				newPosition.push_back({ x1, y1 });
			}
		}
		else
		{
			while (x1 < x2 && y1 > y2)
			{
				x1++;
				y1--;

				newPosition.push_back({ x1, y1 });
			}
		}
	}

	return newPosition;
}

PositionMatrix Bishop::AllMoves(Position p) const
{
	PositionMatrix newMatrix;

	newMatrix.resize(4);

	int x = p.x,
		y = p.y;

	while (x > 0 && y > 0)
	{
		x--;
		y--;

		newMatrix[0].push_back({ x, y });
	}

	x = p.x;
	y = p.y;

	while (x < 7 && y > 0)
	{
		x++;
		y--;

		newMatrix[1].push_back({ x, y });
	}

	x = p.x;
	y = p.y;

	while (x > 0 && y < 7)
	{
		x--;
		y++;

		newMatrix[2].push_back({ x, y });
	}

	x = p.x;	y = p.y;

	while (x < 7 && y < 7)
	{
		x++;
		y++;

		newMatrix[3].push_back({ x, y });
	}

	return newMatrix;
}

bool Bishop::BishopMove(Position p1, Position p2)
{
	auto x1 = p1.x,
		x2 = p2.x,
		y1 = p1.y,
		y2 = p2.y;

	return (AbsValue(x2, x1) == AbsValue(y2, y1) && AbsValue(x2, x1) != 0);
}
