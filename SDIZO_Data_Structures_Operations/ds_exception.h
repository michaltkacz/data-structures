#pragma once
#include <exception>

class ds_exception : public std::exception
{
public:
	ds_exception(const char* msg) : std::exception(msg) {}
};
