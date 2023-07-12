#include "Bishop.h"

bool Bishop::IsMoveRegular(int x_curr, int y_curr, int x_next, int y_next)
{
	return (std::abs(x_curr - x_next) == std::abs(y_curr - y_next));
}

Bishop::Bishop(EColor color) : Piece(EPieceType::Bishop, color)
{
}
