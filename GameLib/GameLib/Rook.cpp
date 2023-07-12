#include "Rook.h"


bool Rook::IsMoveRegular(int x_curr, int y_curr, int x_next, int y_next)
{
	return((x_curr == x_next) ^ (y_curr == y_next));
}

Rook::Rook(EColor color): Piece(EPieceType::Rook, color)
{
}
