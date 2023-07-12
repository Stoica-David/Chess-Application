#include "Queen.h"

Queen::Queen():Piece(EPieceType::Queen)
{
}

Queen::Queen(EColor color):Piece(EPieceType::Queen, color)
{
}
