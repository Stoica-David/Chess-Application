#pragma once
#include "IException.h"
class MoveException :  public IException
{
public:
	MoveException(std::string);
};

