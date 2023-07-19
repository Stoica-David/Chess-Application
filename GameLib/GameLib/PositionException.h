#pragma once
#include "IException.h"
class PositionException:public IException
{
public:
	PositionException(std::string);
};

