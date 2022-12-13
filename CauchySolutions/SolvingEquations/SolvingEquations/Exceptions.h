#pragma once
#include <iostream>
class Exception : public std::exception
{
protected:
	std::string error_msg;
public:
    virtual const char* what() const noexcept override = 0;
	virtual ~Exception() = default;
};

//===================================================================================
//===================================================================================
//===================================================================================


class InputUserValueException : public Exception
{
public:
	InputUserValueException(const std::string&);
    const char* what() const noexcept override;

};


//===================================================================================
//===================================================================================
//===================================================================================
class MatrixErrorException : public Exception
{
public:
	MatrixErrorException(const std::string&);
    const char* what() const noexcept override;

};

//===================================================================================
//===================================================================================
//===================================================================================
class NormErrorException : public Exception
{
public:
	NormErrorException(const std::string&);
    const char* what() const noexcept override;

};

//===================================================================================
//===================================================================================
//===================================================================================

