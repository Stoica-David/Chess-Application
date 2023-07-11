#include "Pawn.h"

Pawn::Pawn() : Piece("Pawn")
{
}

Pawn::Pawn(EColor) : Piece("Pawn", color)
{
}
