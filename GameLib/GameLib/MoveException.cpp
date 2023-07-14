#include "MoveException.h"

MoveException::MoveException():message("[Move] The move cannot be done by the piece!")
{

}

std::string MoveException::GetMessage()
{
	return message;
}
