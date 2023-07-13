#include "Knight.h"

bool Knight::IsMoveRegular(Position p1, Position p2)
{
    //return ((std::abs(x_next - x_curr) == 2 && std::abs(y_next - y_curr) == 1) || (std::abs(x_next - x_curr) == 1 && std::abs(y_next - y_curr) == 2));
    return ((std::abs(p2.first - p1.first) == 2 && std::abs(p2.second - p1.second) == 1) || (std::abs(p2.first - p1.first) == 1 && std::abs(p2.second - p1.second) == 2));
}

PositionList Knight::DeterminePattern(Position p1, Position p2)
{
    return {};
}

Knight::Knight(EColor color):Piece(EPieceType::Knight, color)
{
}
