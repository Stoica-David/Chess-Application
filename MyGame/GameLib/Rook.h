#pragma once
#include "Piece.h"

class Rook :public Piece
{
public:
	// Constructors
	Rook();
	Rook(bool, std::string);

	// Other methods
	std::list<std::string> calculatePossiblePositions();
	bool checkMove(std::string);
};