#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"

Queen::Queen(EColor color) :Piece(EPieceType::Queen, color)
{
}

bool Queen::IsMoveRegular(Position p1, Position p2) const
{
	int x1 = p1.first, y1 = p1.second, x2 = p2.first, y2 = p2.second;

	return (((x1 == x2) ^ (y1 == y2)) || (AbsValue(x2, x1) == AbsValue(y2, y1) && (x2 != x1 || y2 != y1)));
}

PositionList Queen::DeterminePattern(Position p1, Position p2) const
{
	PositionList finalNewPosition;
	PositionList newPosition;

	int x1 = p1.first, y1 = p1.second, x2 = p2.first, y2 = p2.second;

	if (x1 == x2 || y1 == y2)
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

PositionMatrix Queen::AllMoves(Position p) const
{
	Rook R(EColor::White);
	Bishop B(EColor::White);
	PositionMatrix newMatrix1 = R.AllMoves(p);
	PositionMatrix newMatrix2 = B.AllMoves(p);
	PositionMatrix newMatrix;
	PositionList newList1;
	PositionList newList2;

	newMatrix.resize(8);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < newMatrix1[i].size(); j++)
		{
			newMatrix[i].push_back(newMatrix1[i][j]);
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < newMatrix2[i].size(); j++)
		{
			newMatrix[i + 4].push_back(newMatrix2[i][j]);
		}
	}

	return newMatrix;
}
