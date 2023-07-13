#include "Knight.h"

bool Knight::IsMoveRegular(Position p1, Position p2)
{
    return ((std::abs(p2.first - p1.first) == 2 && std::abs(p2.second - p1.second) == 1) || (std::abs(p2.first - p1.first) == 1 && std::abs(p2.second - p1.second) == 2));
}

PositionList Knight::DeterminePattern(Position p1, Position p2)
{
    PositionList newPattern;

    if (IsInTable(p2.first, p2.second))
    {
        newPattern.push_back(p2);
    }

    return newPattern;
}

Knight::Knight(EColor color):Piece(EPieceType::Knight, color)
{
}
