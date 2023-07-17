#include "PositionException.h"

PositionException::PositionException():message("[Position] The given position is out of the table")
{
}

std::string PositionException::GetMessage() const
{
	return message;
}
