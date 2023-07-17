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

PositionMatrix Queen::AllMoves(Position p)
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
