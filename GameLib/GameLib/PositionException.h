#pragma once

#include "ChessException.h"

class PositionException : public ChessException
{
public:
	// Constructor
	PositionException(const std::string&);
};

