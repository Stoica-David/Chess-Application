#include "Rook.h"

Rook::Rook(EColor color) : Piece(EPieceType::Rook, color)
{
}

bool Rook::IsMoveRegular(Position p1, Position p2) const
{
	return(RookMove(p1, p2));
}

PositionList Rook::DeterminePattern(Position p1, Position p2) const
{
	PositionList newPattern;

	auto x1 = p1.x,
		 x2 = p2.x,
		 y1 = p1.y,
		 y2 = p2.y;

	if (x1 == x2)
	{
		if (y1 <= y2)
		{
			for (int i = y1; i <= y2; i++)
			{
				if (i != y1)
					newPattern.push_back({ x1, i });
			}
		}
		else
			if (y1 > y2)
			{
				for (int i = y1; i >= y2; i--)
				{
					if (i != y1)
						newPattern.push_back({ x1, i });
				}
			}
	}
	else
	{
		if (x1 <= x2)
		{
			for (int i = x1; i <= x2; i++)
			{
				if (i != x1)
					newPattern.push_back({ i, y1 });
			}
		}
		else
			if (x1 > x2)
			{
				for (int i = x1; i >= x2; i--)
				{
					if (i != x1)
						newPattern.push_back({ i, y1 });
				}
			}
	}

	return newPattern;
}

PositionMatrix Rook::AllMoves(Position p) const
{
	PositionMatrix newMatrix;

	newMatrix.resize(4);

	Position pAux = p;

	while (pAux.x > 0)
	{
		pAux.x--;
		newMatrix[0].push_back(pAux);
	}

	pAux = p;

	while (pAux.y < 7)
	{
		pAux.y++;
		newMatrix[1].push_back(pAux);
	}

	pAux = p;

	while (pAux.x < 7)
	{
		pAux.x++;
		newMatrix[2].push_back(pAux);
	}

	pAux = p;

	while (pAux.y > 0)
	{
		pAux.y--;
		newMatrix[3].push_back(pAux);
	}

	return newMatrix;
}

bool Rook::RookMove(Position p1, Position p2)
{
	auto x1 = p1.x,
		x2 = p2.x,
		y1 = p1.y,
		y2 = p2.y;

	return ((x1 == x2) ^ (y1 == y2));
}
