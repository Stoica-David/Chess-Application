#pragma once
#include "IException.h"
class MoveException :  public IException
{
public:
	MoveException();
	std::string GetMessage() const override;
private:
	std::string message;
};

