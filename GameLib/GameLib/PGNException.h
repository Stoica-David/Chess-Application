#pragma once

#include "ChessException.h"

class PGNException : public ChessException
{
public:
	// Constructor
	PGNException(const std::string&);
};

