#include "Bishop.h"

bool Bishop::IsMoveRegular(Position p1, Position p2)
{
	return (AbsValue(p1.first, p2.first) == AbsValue(p1.second, p2.second) && (p1.first != p2.first && p1.second != p2.second));
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

PositionList Bishop::AllMoves(Position p)
{
	PositionList newList;
	
	Position pAux = p;
	while (pAux.first > 0 && pAux.second > 0)
	{
		pAux.first--;
		pAux.second--;

		newList.push_back({ pAux.first, pAux.second });
	}

	pAux = p;

	while (pAux.first < 7 && pAux.second > 0)
	{
		pAux.first++;
		pAux.second--;

		newList.push_back({ pAux.first, pAux.second });
	}

	pAux = p;

	while (pAux.first > 0 && pAux.second < 7)
	{
		pAux.first--;
		pAux.second++;

		newList.push_back({ pAux.first, pAux.second });
	}

	pAux = p;

	while (pAux.first < 7 && pAux.second < 7)
	{
		pAux.first++;
		pAux.second++;

		newList.push_back({ pAux.first, pAux.second });
	}

	return newList;
}

Bishop::Bishop(EColor color) : Piece(EPieceType::Bishop, color)
{
}
