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

PositionList King::AllMoves(Position p)
{
	PositionList newList;
	if(IsInTable( p.first - 1, p.second - 1))
	newList.push_back({ p.first - 1, p.second - 1 });
	if (IsInTable(p.first - 1, p.second))
	newList.push_back({ p.first - 1, p.second });
	if (IsInTable(p.first - 1, p.second + 1))
	newList.push_back({ p.first - 1, p.second  + 1});
	if (IsInTable(p.first , p.second - 1))
	newList.push_back({ p.first , p.second  - 1});
	if (IsInTable(p.first , p.second + 1))
	newList.push_back({ p.first , p.second  + 1});
	if (IsInTable(p.first + 1, p.second - 1))
	newList.push_back({ p.first + 1 , p.second  - 1});
	if (IsInTable(p.first + 1, p.second ))
	newList.push_back({ p.first + 1 , p.second  });
	if (IsInTable(p.first + 1, p.second + 1))
	newList.push_back({ p.first + 1 , p.second + 1 });
	return newList;
}
