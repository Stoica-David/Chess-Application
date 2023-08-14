#pragma once

#include "ChessException.h"

class StillCheckException : public ChessException
{
public:
	// Constructor
	StillCheckException(const std::string&);
};

