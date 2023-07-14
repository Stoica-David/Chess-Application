#include "Bishop.h"

bool Bishop::IsMoveRegular(Position p1, Position p2)
{
	return (std::abs(p1.first - p2.first) == std::abs(p1.second - p2.second) && (p1.first != p2.first && p1.second != p2.second));
}

PositionList Bishop::DeterminePattern(Position p1, Position p2)
{
	PositionList newPosition;

	int x = p1.first, y = p1.second;

	if (x > p2.first)
	{
		if (p2.second > y)
		{
			while (x > p2.first && y < p2.second)
			{
				x--;
				y++;

				newPosition.push_back({ x, y });
			}
		}
		else
		{
			while (x > p2.first && y > p2.second)
			{
				x--;
				y--;

				newPosition.push_back({ x, y });
			}
		}
	}
	else
	{
		if (p2.second > p1.second)
		{
			while (x < p2.first && y < p2.second)
			{
				x++;
				y++;

				newPosition.push_back({ x, y });
			}
		}
		else
		{
			while (x < p2.first && y > p2.second)
			{
				x++;
				y--;

				newPosition.push_back({ x, y });
			}
		}
	}

	return newPosition;
}

Bishop::Bishop(EColor color) : Piece(EPieceType::Bishop, color)
{
}
