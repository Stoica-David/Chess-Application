#include "InTheWayException.h"

InTheWayException::InTheWayException() : message("[InTheWay] There is a piece in the way")
{
}

std::string InTheWayException::GetMessage()
{
	return message;
}
