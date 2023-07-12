#include "Knight.h"

bool Knight::IsMoveRegular(int x_curr, int y_curr, int x_next, int y_next)
{
    return ((std::abs(x_next - x_curr) == 2 && std::abs(y_next - y_curr) == 1) || (std::abs(x_next - x_curr) == 1 && std::abs(y_next - y_curr) == 2));
}

Knight::Knight(EColor color):Piece(EPieceType::Knight, color)
{
}
