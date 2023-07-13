#include "King.h"

King::King(EColor color) : Piece(EPieceType::King, color)
{
}

bool King::IsMoveRegular(Position p1, Position p2)
{
	//return ((std::abs(x_next - x_curr) == 1 && std::abs(y_next - y_curr) == 0)|| (std::abs(x_next - x_curr) == 0 && std::abs(y_next - y_curr) == 1));
	return ((std::abs(p2.first - p1.first) == 1 && std::abs(p2.second - p1.second) == 0)|| (std::abs(p2.first - p1.first) == 0 && std::abs(p2.second - p1.second) == 1));
}
