#include "King.h"


King::King():Piece(EPieceType::King)
{
}

King::King(EColor color) : Piece(EPieceType::King, color)
{
}
