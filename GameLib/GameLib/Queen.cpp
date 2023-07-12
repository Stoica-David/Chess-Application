#include "Queen.h"

Queen::Queen(EColor color):Piece(EPieceType::Queen, color)
{
}

bool Queen::IsMoveRegular(int x_curr, int y_curr, int x_next, int y_next)
{
    return (((x_curr == x_next) ^ (y_curr == y_next)) || (std::abs(x_next - x_curr) == std::abs(y_next - y_curr) && (x_next != x_curr || y_next != y_curr)));
}
