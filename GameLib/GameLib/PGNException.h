#pragma once
#include "ChessException.h"

class PGNException : public ChessException
{
public:
	PGNException(const std::string&);
};

