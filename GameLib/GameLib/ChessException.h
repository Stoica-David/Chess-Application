#pragma once

#include <stdexcept>

class ChessException : public std::logic_error
{
public:
	// Constructors
	ChessException();
	ChessException(const std::string&);
};

