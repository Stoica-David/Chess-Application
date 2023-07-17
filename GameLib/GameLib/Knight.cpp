#include "Knight.h"

bool Knight::IsMoveRegular(Position p1, Position p2)
{
    return ((AbsValue(p2.first, p1.first) == 2 && AbsValue(p2.second, p1.second) == 1) || (AbsValue(p2.first, p1.first) == 1 && AbsValue(p2.second, p1.second) == 2));
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

PositionMatrix Knight::AllMoves(Position p)
{
    PositionMatrix newMatrix;

    newMatrix.resize(8);

    if (IsInTable(p.first - 1, p.second - 2))
        newMatrix[0].push_back({ p.first - 1, p.second - 2});
    if (IsInTable(p.first - 2, p.second - 1))
        newMatrix[1].push_back({ p.first - 2, p.second - 1 });
    if(IsInTable(p.first - 2, p.second + 1))
        newMatrix[2].push_back({ p.first - 2, p.second + 1 });
    if(IsInTable(p.first - 1, p.second + 2))
        newMatrix[3].push_back({ p.first - 1, p.second + 2 });
	if (IsInTable(p.first + 1, p.second + 2))
        newMatrix[4].push_back({ p.first + 1, p.second + 2 });
	if (IsInTable(p.first + 2, p.second + 1))
        newMatrix[5].push_back({ p.first + 2, p.second + 1 });
	if (IsInTable(p.first + 2, p.second - 1))
        newMatrix[6].push_back({ p.first + 2, p.second - 1 });
    if (IsInTable(p.first + 1, p.second - 2))
        newMatrix[7].push_back({ p.first + 1, p.second - 2 });

    return newMatrix;
}

Knight::Knight(EColor color):Piece(EPieceType::Knight, color)
{
}
