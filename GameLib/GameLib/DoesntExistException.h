#pragma once

#include "ChessException.h"

class DoesntExistException : public ChessException
{
public:
	// Constructor
	DoesntExistException(const std::string&);
};

