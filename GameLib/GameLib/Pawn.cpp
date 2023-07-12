#include "Pawn.h"

Pawn::Pawn(EColor color) : Piece(EPieceType::Pawn, color)
{
}

bool Pawn::IsMoveRegular(int x_curr, int y_curr, int x_next, int y_next)
{ 
	return (((((this->m_color == EColor::white) && (x_curr == 6) && (x_next < x_curr)) || (this->m_color == EColor::black) && (x_curr == 1) && (x_next > x_curr)) && ((std::abs(x_next - x_curr) >= 1) && (std::abs(x_next - x_curr) < 3))) || (((this->m_color == EColor::white) && (x_next - x_curr == -1)) ||  (((this->m_color == EColor::black) && (x_next - x_curr == 1)))) || ((this->m_color == EColor::white && x_next - x_curr == -1 && std::abs(y_next - y_curr)) || (this->m_color == EColor::black && x_next - x_curr == 1 && std::abs(y_next - y_curr))));
}
