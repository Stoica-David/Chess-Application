#include "Queen.h"

Queen::Queen(EColor color):Piece(EPieceType::Queen, color)
{
}

bool Queen::IsMoveRegular(Position p1, Position p2)
{
    //return (((x_curr == x_next) ^ (y_curr == y_next)) || (std::abs(x_next - x_curr) == std::abs(y_next - y_curr) && (x_next != x_curr || y_next != y_curr)));
    return (((p1.first == p2.first) ^ (p1.second == p2.second)) || (std::abs(p2.first - p1.first) == std::abs(p2.second - p1.second) && (p2.first != p1.first || p2.second != p1.second)));
}
