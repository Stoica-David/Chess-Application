#include "Knight.h"

bool Knight::IsMoveRegular(Position p1, Position p2) const
{
    auto x1 = p1.first, y1 = p1.second, x2 = p2.first, y2 = p2.second;
    return ((AbsValue(x2, x1) == 2 && AbsValue(y2, y1) == 1) || (AbsValue(x2, x1) == 1 && AbsValue(y2, y1) == 2));
}

PositionList Knight::DeterminePattern(Position p1, Position p2) const
{
    PositionList newPattern;

    if (IsInTable(p2.first, p2.second))
    {
        newPattern.push_back(p2);
    }

    return newPattern;
}

PositionMatrix Knight::AllMoves(Position p) const
{
    auto x = p.first, y = p.second;
    PositionMatrix newMatrix;

    newMatrix.resize(8);

    if (IsInTable(x - 1, y - 2))
        newMatrix[0].push_back({ x - 1, y - 2});
    if (IsInTable(x - 2, y - 1))
        newMatrix[1].push_back({ x - 2, y - 1 });
    if(IsInTable(x - 2, y + 1))
        newMatrix[2].push_back({ x - 2, y + 1 });
    if(IsInTable(x - 1, y + 2))
        newMatrix[3].push_back({ x - 1, y + 2 });
	if (IsInTable(x + 1, y + 2))
        newMatrix[4].push_back({ x + 1, y + 2 });
	if (IsInTable(x + 2, y + 1))
        newMatrix[5].push_back({ x + 2, y + 1 });
	if (IsInTable(x + 2, y - 1))
        newMatrix[6].push_back({ x + 2, y - 1 });
    if (IsInTable(x + 1, y - 2))
        newMatrix[7].push_back({ x + 1, y - 2 });

    return newMatrix;
}

Knight::Knight(EColor color):Piece(EPieceType::Knight, color)
{
}
