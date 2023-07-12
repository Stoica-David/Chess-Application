#include "Pawn.h"


Pawn::Pawn()
{
}

Pawn::Pawn(EColor) : Piece(EPieceType::Pawn, m_color)
{
}
