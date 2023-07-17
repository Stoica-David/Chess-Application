#pragma once

#include <stdexcept>
#include <exception>
class IException : public std::runtime_error::exception
{
public:
	virtual std::string GetMessage()const =0;
	virtual ~IException() = default;
};

