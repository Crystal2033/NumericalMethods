#include "Exceptions.h"

BadRangeException::BadRangeException(const std::string& errorMsg)
{
	this->errorMsg = errorMsg;
}

const char* BadRangeException::what() const noexcept
{
    return errorMsg.c_str();
}
