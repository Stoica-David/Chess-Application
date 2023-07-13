#include "Rook.h"


bool Rook::IsMoveRegular(Position p1, Position p2)
{
	return((p1.first == p2.first) ^ (p1.second == p2.second));
}

PositionList Rook::DeterminePattern(Position p1, Position p2)
{
	PositionList newPattern;

	if (p1.first == p2.first)
	{
		if (p1.second <= p2.second)
		{
			for (int i = p1.second; i <= p2.second; i++)
			{
				if (i != p1.second)
					newPattern.push_back(std::make_pair(p1.first, i));
			}
		}
		else
			if (p1.second > p2.second)
			{
				for (int i = p1.second; i >= p2.second; i--)
				{
					if (i != p1.second)
						newPattern.push_back(std::make_pair(p1.first, i));
				}
			}
	}
	else
	{
		if (p1.first <= p2.first)
		{
			for (int i = p1.first; i <= p2.first; i++)
			{
				if (i != p1.first)
					newPattern.push_back(std::make_pair(i, p1.second));
			}
		}
		else
			if (p1.first > p2.first)
			{
				for (int i = p1.first; i >= p2.first; i--)
				{
					if (i != p1.first)
						newPattern.push_back(std::make_pair(i, p1.second));
				}
			}
	}

	return newPattern;
}

Rook::Rook(EColor color) : Piece(EPieceType::Rook, color)
{
}
