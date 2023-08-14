#pragma once

#include "ChessException.h"

class InTheWayException : public ChessException
{
public:
	// Constructor
	InTheWayException(const std::string&);
};

