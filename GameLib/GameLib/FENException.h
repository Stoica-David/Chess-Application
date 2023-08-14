#pragma once

#include "ChessException.h"

class FENException : public ChessException
{
public:
	// Constructor
	FENException(const std::string&);
};

