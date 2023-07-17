#include "King.h"

King::King(EColor color) : Piece(EPieceType::King, color)
{
}

bool King::IsMoveRegular(Position p1, Position p2) const
{
	int x1 = p1.first, y1 = p1.second, x2 = p2.first, y2 = p2.second;
	return ((AbsValue(x2, x1) == 1 && AbsValue(y2, y1) == 0) || (AbsValue(x2, x1) == 0 && AbsValue(y2, y1) == 1) || ((AbsValue(x2, x1) == 1 && AbsValue(y2, y1) == 1)));
}

PositionList King::DeterminePattern(Position p1, Position p2) const
{
	PositionList newPattern = { p2 };
	return newPattern;
}

PositionMatrix King::AllMoves(Position p) const
{
	PositionMatrix newMatrix;
	
	int x = p.first, y = p.second;

	newMatrix.resize(8);

	if(IsInTable( x - 1, y - 1))
		newMatrix[0].push_back({ x - 1, y - 1 });
	if (IsInTable(x - 1, y))
		newMatrix[1].push_back({ x - 1, y });
	if (IsInTable(x - 1, y + 1))
		newMatrix[2].push_back({ x - 1, y + 1});
	if (IsInTable(x , y - 1))
		newMatrix[3].push_back({ x , y - 1});
	if (IsInTable(x , y + 1))
		newMatrix[4].push_back({ x , y + 1});
	if (IsInTable(x + 1, y - 1))
		newMatrix[5].push_back({ x + 1 , y - 1});
	if (IsInTable(x + 1, y))
		newMatrix[6].push_back({ x + 1 , y});
	if (IsInTable(x + 1, y + 1))
		newMatrix[7].push_back({ x + 1 , y + 1});

	return newMatrix;
}
