#include "Bishop.h"

bool Bishop::IsMoveRegular(Position p1, Position p2)
{
	return (std::abs(p1.first - p2.first) == std::abs(p1.second - p2.second) && (p1.first != p2.first && p1.second != p2.second));
}

Bishop::Bishop(EColor color) : Piece(EPieceType::Bishop, color)
{
}
