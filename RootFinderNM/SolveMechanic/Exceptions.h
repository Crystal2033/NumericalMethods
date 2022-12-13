#pragma once
#include <iostream>
class BadRangeException : public std::exception {
public:
	BadRangeException(const std::string& errorMsg);
    const char* what() const noexcept override;

private:
	std::string errorMsg;
};
