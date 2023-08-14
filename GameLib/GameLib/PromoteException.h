#pragma once

#include "ChessException.h"

class PromoteException : public ChessException
{
public:
	// Constructor
	PromoteException(const std::string&);
};

