#include "Bishop.h"

//bool Bishop::IsMoveValid(int x_curr, int y_curr, int x_next, int y_next)
//{
//	if (x_next == y_next || x_next + y_next == 8)
//		return true;
//	return false;
//}

Bishop::Bishop(EColor color) : Piece(EPieceType::Bishop, color)
{
}
