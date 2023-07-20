#pragma once

#include <stdexcept>

class ChessException : public std::logic_error::exception
{
public:
	ChessException();
	ChessException(const std::string&);
};

