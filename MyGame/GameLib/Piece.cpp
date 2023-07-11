#include<iostream>
#include "Piece.h"

Piece::Piece()
{
	this->color = false;
	this->curPosition = "A1";
	this->possiblePositions = {};
}

Piece::Piece(bool color, std::string curPosition)
{
	this->color = color;
	this->curPosition = curPosition;
}

void Piece::setColor(bool color)
{
	this->color = color;
}

void Piece::setCurPosition(std::string curPosition)
{
	this->curPosition = curPosition;
}

bool Piece::getColor()
{
	return this->color;
}

std::string Piece::getCurPosition()
{
	return this->curPosition;
}

std::list<std::string> Piece::getPossiblePositions()
{
	return this->possiblePositions;
}

void Piece::showPossiblePositions()
{
	for (auto current : this->possiblePositions)
	{
		std::cout << current << " ";
	}
}

bool Piece::checkPosition(std::string curPosition)
{
	return (curPosition[0] >= 'A' && curPosition[0] <= 'H' && curPosition[1] >= 1 && curPosition[1] <= 8);
}

void Piece::clearPossiblePositions()
{
	this->possiblePositions.clear();
}
