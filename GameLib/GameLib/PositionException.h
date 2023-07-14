#pragma once
#include "IException.h"
class PositionException:public IException
{
public:
	PositionException();
	std::string GetMessage() override;
private:
	std::string message;
};

