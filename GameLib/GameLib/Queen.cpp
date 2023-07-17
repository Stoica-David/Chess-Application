#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"

Queen::Queen(EColor color) :Piece(EPieceType::Queen, color)
{
}

bool Queen::IsMoveRegular(Position p1, Position p2)
{
	return (((p1.first == p2.first) ^ (p1.second == p2.second)) || (AbsValue(p2.first, p1.first) == AbsValue(p2.second, p1.second) && (p2.first != p1.first || p2.second != p1.second)));
}

PositionList Queen::DeterminePattern(Position p1, Position p2)
{
	PositionList finalNewPosition;
	PositionList newPosition;

	if (p1.first == p2.first || p1.second == p2.second)
	{
		Rook R(EColor::White);
		newPosition = R.DeterminePattern(p1, p2);

		for (int i = 0; i < newPosition.size(); i++)
		{
			finalNewPosition.push_back(newPosition[i]);
		}
	}
	else
	{
		Bishop B(EColor::White);
		newPosition = B.DeterminePattern(p1, p2);

		for (int i = 0; i < newPosition.size(); i++)
		{
			finalNewPosition.push_back(newPosition[i]);
		}
	}

	return finalNewPosition;
}

PositionList Queen::AllMoves(Position p)
{
	Rook R(EColor::White);
	Bishop B(EColor::White);
	PositionList newList1 = R.AllMoves(p);
	PositionList newList2 = B.AllMoves(p);
	PositionList newList;

	for (int i = 0; i < newList1.size(); i++)
	{
		newList.push_back(newList1[i]);
	}
	
	for (int i = 0; i < newList2.size(); i++)
	{
		newList.push_back(newList2[i]);
	}

	return newList;
}
