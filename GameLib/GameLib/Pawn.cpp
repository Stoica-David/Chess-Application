#include "Pawn.h"

Pawn::Pawn(EColor color) : Piece(EPieceType::Pawn, color)
{
}

bool Pawn::IsMoveRegular(Position p1, Position p2)
{ 
	//return (((((this->m_color == EColor::White) && (x_curr == 6) && (x_next < x_curr)) || (this->m_color == EColor::Black) && (x_curr == 1) && (x_next > x_curr)) && ((std::abs(x_next - x_curr) >= 1) && (std::abs(x_next - x_curr) < 3))) || (((this->m_color == EColor::White) && (x_next - x_curr == -1)) ||  (((this->m_color == EColor::Black) && (x_next - x_curr == 1)))) || ((this->m_color == EColor::White && x_next - x_curr == -1 && std::abs(y_next - y_curr)) || (this->m_color == EColor::Black && x_next - x_curr == 1 && std::abs(y_next - y_curr))));
	return (((((this->m_color == EColor::White) && (p1.first == 6) && (p2.first < p1.first)) || (this->m_color == EColor::Black) && (p1.first == 1) && (p2.first > p1.first)) && ((std::abs(p2.first - p1.first) >= 1) && (std::abs(p2.first - p1.first) < 3))) || (((this->m_color == EColor::White) && (p2.first - p1.first == -1)) ||  (((this->m_color == EColor::Black) && (p2.first - p1.first == 1)))) || ((this->m_color == EColor::White && p2.first - p1.first == -1 && std::abs(p2.second - p1.second)) || (this->m_color == EColor::Black && p2.first - p1.first == 1 && std::abs(p2.second - p1.second))));
}
