#pragma once
#include "ChessException.h"
class FENException :   public ChessException
{
public:
	FENException(const std::string&);
};

