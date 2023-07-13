#include "Bishop.h"

bool Bishop::IsMoveRegular(Position p1, Position p2)
{
	return (std::abs(p1.first - p2.first) == std::abs(p1.second - p2.second) && (p1.first != p2.first && p1.second != p2.second));
}

PositionList Bishop::DeterminePattern(Position p1, Position p2)
{
	PositionList newPosition;

	if (p1.first > p2.first)
	{
		if (p2.second > p1.second)
		{
			while (p1.first > p2.first && p1.second < p2.second)
			{
				p1.first--;
				p1.second++;

				newPosition.push_back({ p1.first, p1.second });
			}
		}
		else
		{
			while (p1.first > p2.first && p1.second > p2.second)
			{
				p1.first--;
				p1.second--;

				newPosition.push_back({ p1.first, p1.second });
			}
		}
	}
	else
	{
		if (p2.second > p1.second)
		{
			while (p1.first < p2.first && p1.second < p2.second)
			{
				p1.first++;
				p1.second++;

				newPosition.push_back({ p1.first, p1.second });
			}
		}
		else
		{
			while (p1.first < p2.first && p1.second > p2.second)
			{
				p1.first++;
				p1.second--;

				newPosition.push_back({ p1.first, p1.second });
			}
		}
	}

	return newPosition;
}

Bishop::Bishop(EColor color) : Piece(EPieceType::Bishop, color)
{
}
