#include "Pawn.h"

Pawn::Pawn(EColor color) : Piece(EPieceType::Pawn, color)
{
}

bool Pawn::IsMoveRegular(Position p1, Position p2)
{ 
	return (((((m_color == EColor::White) && (p1.first == 6) && (p2.first < p1.first)) || (m_color == EColor::Black) && (p1.first == 1) && (p2.first > p1.first)) && ((std::abs(p2.first - p1.first) >= 1) && (std::abs(p2.first - p1.first) < 3))) || (((m_color == EColor::White) && (p2.first - p1.first == -1)) ||  (((m_color == EColor::Black) && (p2.first - p1.first == 1)))) || ((m_color == EColor::White && p2.first - p1.first == -1 && std::abs(p2.second - p1.second)) || (m_color == EColor::Black && p2.first - p1.first == 1 && std::abs(p2.second - p1.second))));
}

PositionList Pawn::DeterminePattern(Position p1, Position p2)
{
	PositionList newPattern;

	if (std::abs(p1.first - p2.first) == 2)
	{
		if (m_color == EColor::White)
		{
			newPattern.push_back({ p1.first - 1, p1.second });
		}
		else
		{
			newPattern.push_back({ p1.first + 1, p1.second });
		}
		newPattern.push_back(p2);
	}
	else
	{
		newPattern.push_back(p2);
	}

	return newPattern;
}
