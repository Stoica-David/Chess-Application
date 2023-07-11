#include "Piece.h"

Piece::Piece():name("-"), color(EColor::none)
{
}

Piece::Piece(std::string name, EColor color)
{
	this->name = name;
	this->color = color;
}

std::string Piece::GetName()
{
	return this->name;
}
