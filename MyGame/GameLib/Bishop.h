#pragma once
#include "Piece.h"

class Bishop :public Piece
{
public:
	// Constructors 
	Bishop();
	Bishop(bool, std::string);

	// Other methods
	std::list<std::string> calculatePossiblePositions();
	bool checkMove(std::string);
};