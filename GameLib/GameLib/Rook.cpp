#include "Rook.h"


bool Rook::IsMoveRegular(Position p1, Position p2) const
{
	auto x1 = p1.first,
		x2 = p2.first,
		y1 = p1.second,
		y2 = p2.second;

	return((x1 == x2) ^ (y1 == y2));
}

PositionList Rook::DeterminePattern(Position p1, Position p2) const
{
	auto x1 = p1.first,
		x2 = p2.first,
		y1 = p1.second,
		y2 = p2.second;

	PositionList newPattern;

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

	while (pAux.first > 0)
	{
		pAux.first--;
		newMatrix[0].push_back(pAux);
	}

	pAux = p;

	while (pAux.second < 7)
	{
		pAux.second++;
		newMatrix[1].push_back(pAux);
	}

	pAux = p;

	while (pAux.first < 7)
	{
		pAux.first++;
		newMatrix[2].push_back(pAux);
	}

	pAux = p;

	while (pAux.second > 0)
	{
		pAux.second--;
		newMatrix[3].push_back(pAux);
	}

	return newMatrix;
}

Rook::Rook(EColor color) : Piece(EPieceType::Rook, color)
{
}
