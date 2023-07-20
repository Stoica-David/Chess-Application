#pragma once

#include "IException.h"

class MoveException :  public IException
{
public:
	MoveException(const std::string&);
};

