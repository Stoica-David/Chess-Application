#pragma once

#include "ChessException.h"

class MoveException : public ChessException
{
public:
	// Constructor
	MoveException(const std::string&);
};

