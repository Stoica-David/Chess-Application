#include "King.h"

King::King(EColor color) : Piece(EPieceType::King, color)
{
}

bool King::IsMoveRegular(Position p1, Position p2)
{
	return ((AbsValue(p2.first, p1.first) == 1 && AbsValue(p2.second, p1.second) == 0) || (AbsValue(p2.first, p1.first) == 0 && AbsValue(p2.second, p1.second) == 1) || ((AbsValue(p2.first, p1.first) == 1 && AbsValue(p2.second, p1.second) == 1)));
}

PositionList King::DeterminePattern(Position p1, Position p2)
{
	PositionList newPattern = { p2 };
	return newPattern;
}

PositionMatrix King::AllMoves(Position p)
{
	PositionMatrix newMatrix;

	newMatrix.resize(8);

	if(IsInTable( p.first - 1, p.second - 1))
		newMatrix[0].push_back({ p.first - 1, p.second - 1 });
	if (IsInTable(p.first - 1, p.second))
		newMatrix[1].push_back({ p.first - 1, p.second });
	if (IsInTable(p.first - 1, p.second + 1))
		newMatrix[2].push_back({ p.first - 1, p.second  + 1});
	if (IsInTable(p.first , p.second - 1))
		newMatrix[3].push_back({ p.first , p.second  - 1});
	if (IsInTable(p.first , p.second + 1))
		newMatrix[4].push_back({ p.first , p.second  + 1});
	if (IsInTable(p.first + 1, p.second - 1))
		newMatrix[5].push_back({ p.first + 1 , p.second  - 1});
	if (IsInTable(p.first + 1, p.second ))
		newMatrix[6].push_back({ p.first + 1 , p.second  });
	if (IsInTable(p.first + 1, p.second + 1))
		newMatrix[7].push_back({ p.first + 1 , p.second + 1 });

	return newMatrix;
}
