#pragma once

#include <stdexcept>

class ChessException : public std::runtime_error
{
public:
	ChessException();
	ChessException(const std::string&);
};

