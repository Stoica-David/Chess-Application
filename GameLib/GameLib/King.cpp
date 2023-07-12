#include "King.h"

King::King(EColor color) : Piece(EPieceType::King, color)
{
}

bool King::IsMoveRegular(int x_curr, int y_curr, int x_next, int y_next)
{
	return ((std::abs(x_next - x_curr) == 1 && std::abs(y_next - y_curr) == 0)|| (std::abs(x_next - x_curr) == 0 && std::abs(y_next - y_curr) == 1));
}
