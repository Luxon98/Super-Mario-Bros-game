#include "FileNotLoadedException.h"


FileNotLoadedException::FileNotLoadedException(const std::string &message) : std::runtime_error(""), 
		exceptionMessage(message) {}

const char* FileNotLoadedException::what() const noexcept 
{
	return exceptionMessage.c_str();
}