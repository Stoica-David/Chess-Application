#include "Pawn.h"

Pawn::Pawn(EColor color) : Piece(EPieceType::Pawn, color)
{
}

bool Pawn::IsMoveRegular(Position p1, Position p2)
{ 
	if (!(((IsWhite() && (p1.first == 6) && (p2.first < p1.first)) || IsBlack() && (p1.first == 1) && (p2.first > p1.first)) && ((AbsValue(p2.first, p1.first) >= 1 && (p2.second == p1.second)) && (AbsValue(p2.first, p1.first) < 3)))) // Moves wrong forward (one/two squares)
	{
		return false;
	}

	if ((IsWhite() && (p2.first - p1.first == 1)) || (IsBlack() && (p2.first - p1.first == -1))) // Moves backwards
	{
		return false;
	}

	if ((IsWhite() && p2.first - p1.first == 1 && AbsValue(p2.second, p1.second)) || (IsBlack() && p2.first - p1.first == -1 && AbsValue(p2.second, p1.second))) // Moves wrong diagonally
	{
		return false;
	}

	return true;
}

PositionList Pawn::DeterminePattern(Position p1, Position p2)
{
	PositionList newPattern;

	newPattern.push_back(p2);

	return newPattern;
}

PositionList Pawn::AllMoves(Position p)
{
	PositionList newList;

	if (IsWhite() && (p.first == 6))
	{
		newList.push_back({ p.first - 1, p.second });
		newList.push_back({ p.first - 2, p.second });
		newList.push_back({ p.first - 1, p.second - 1 });
		newList.push_back({ p.first - 1, p.second + 1 });
	}

	if (IsBlack() && (p.first == 1))
	{
		newList.push_back({ p.first + 1, p.second });
		newList.push_back({ p.first + 2, p.second });
		newList.push_back({ p.first + 1, p.second - 1 });
		newList.push_back({ p.first + 1, p.second + 1 });
	}

	return newList;
}
