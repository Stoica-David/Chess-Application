#include "Pawn.h"

Pawn::Pawn(EColor color) : Piece(EPieceType::Pawn, color)
{
}

bool Pawn::IsMoveRegular(Position p1, Position p2) const
{

	int x1 = p1.first, y1 = p1.second, x2 = p2.first, y2 = p2.second;

	if (!(((IsColor(EColor::White) && (x1 == 6) && (x2 < x1)) || IsColor(EColor::Black) && (x1 == 1) && (x2 > x1)) && ((AbsValue(x2, x1) >= 1 && (y2 == y1)) && (AbsValue(x2, x1) < 3)))) // Moves wrong forward (one/two squares)
	{
		return false;
	}

	if ((IsColor(EColor::White) && (x2 - x1 == 1)) || (IsColor(EColor::Black) && (x2 - x1 == -1))) // Moves backwards
	{
		return false;
	}

	if ((IsColor(EColor::White) && x2 - x1 == 1 && AbsValue(y2, y1)) || (IsColor(EColor::Black) && x2 - x1 == -1 && AbsValue(y2, y1))) // Moves wrong diagonally
	{
		return false;
	}

	return true;
}

PositionList Pawn::DeterminePattern(Position p1, Position p2) const
{
	PositionList newPattern;

	newPattern.push_back(p2);

	return newPattern;
}

PositionMatrix Pawn::AllMoves(Position p) const
{
	auto x = p.first, y = p.second;
	PositionMatrix newMatrix;

	newMatrix.resize(4);

	if (IsColor(EColor::White))
	{
		newMatrix[0].push_back({ x - 1, y });

		if (x == 6)
			newMatrix[1].push_back({ x - 2, y});

		if (IsInTable({ x - 1, y - 1 }))
			newMatrix[2].push_back({ x - 1, y - 1 });

		if (IsInTable({ x - 1, y + 1 }))
			newMatrix[3].push_back({ x - 1, y + 1 });
	}

	if (IsColor(EColor::Black))
	{
		newMatrix[0].push_back({ x + 1, y });

		if (x == 1)
			newMatrix[1].push_back({ x + 2, y });

		if (IsInTable({ x + 1, y - 1 }))
			newMatrix[2].push_back({ x + 1, y - 1 });

		if (IsInTable({ x + 1, y + 1 }))
			newMatrix[3].push_back({ x + 1, y + 1 });
	}

	return newMatrix;
}
