#pragma once

#include "ChessException.h"

class TurnException : public ChessException
{
public:
    // Constructor
    TurnException(const std::string&);
};

