#include <iostream>
#include <cstring>
#include <malloc.h>
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
	if (this != &rhs) {
		this->_t = rhs._t;
		this->_local = rhs._local;
		std::memcpy(this->_date, rhs._date, sizeof(this->_date));
	}
	return *this;
}

std::string DateTime::getTitle() const
{
	return std::string("DATE | TIME");
}

std::string DateTime::getContent() const
{
	return std::string("");
}

void DateTime::display()
{
	time(&_t);
	_local = localtime(&_t);
	strftime(_date, sizeof(_date), "%a %d %b %G | %T", _local);
	std::cout << "DATE | TIME" << std::endl;
	std::cout << "___________" << std::endl;
	std::cout << _date << std::endl;
	// if (_local != nullptr)
	// 	free(_local);
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
