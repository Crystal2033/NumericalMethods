#include "Exceptions.h"
MatrixErrorException::MatrixErrorException(const std::string& str) {
	error_msg = str;
}

const char* MatrixErrorException::what()const noexcept {
	return error_msg.c_str();
}

InputUserValueException::InputUserValueException(const std::string& str) {
	error_msg = str;
}

const char* InputUserValueException::what()const noexcept {
    return error_msg.c_str();
}

NormErrorException::NormErrorException(const std::string& str) {
	error_msg = str;
}

const char* NormErrorException::what()const noexcept {
	return error_msg.c_str();
}
