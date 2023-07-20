#include "ChessException.h"

ChessException::ChessException(const std::string& message)
	: std::runtime_error(message)
{
}

ChessException::ChessException()
	:std::runtime_error("Unknown exception")
{
}
