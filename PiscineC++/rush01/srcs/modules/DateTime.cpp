#include <iostream>
#include "DateTime.hpp"

DateTime::DateTime()
{}

DateTime::~DateTime()
{}

DateTime::DateTime(DateTime const & src)
{
	*this = src;
}

DateTime & DateTime::operator=(DateTime const & rhs)
{
	if (this != &rhs) {}
	return *this;
}

void DateTime::display()
{
	time(&_t);
	_local = localtime(&_t);
	strftime(_date, sizeof(_date), "%a %d %b %G | %T", _local);
	std::cout << "DATE | TIME" << std::endl;
	std::cout << "___________" << std::endl;
	std::cout << _date << std::endl;
	free(_local);
}

extern "C"
{
	void *createModule() {
		return reinterpret_cast<void *>(new DateTime);
	}

	void deleteModule(void *module) {
		delete reinterpret_cast<DateTime *>(module);
	}
}
