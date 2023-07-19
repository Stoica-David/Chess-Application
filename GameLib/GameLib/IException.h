#pragma once

#include <stdexcept>

class IException : public std::logic_error::exception
{
public:
	virtual ~IException() = default;
};

