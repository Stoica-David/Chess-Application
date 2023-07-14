#pragma once
#include "IException.h"
class InTheWayException :  public IException
{
public:
	InTheWayException();
	std::string GetMessage() override;
private:
	std::string message;
};

