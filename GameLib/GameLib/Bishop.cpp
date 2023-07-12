#include "Bishop.h"

Bishop::Bishop():Piece(EPieceType::Bishop)
{
}

Bishop::Bishop(EColor) : Piece(EPieceType::Bishop, m_color)
{
}
