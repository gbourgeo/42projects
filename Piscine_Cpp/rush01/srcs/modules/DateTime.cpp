#include <iostream>
#include <cstring>
#include <malloc.h>
#include "DateTime.hpp"

DateTime::DateTime()
{
	this->_title = "DATE | TIME";
	DateTime::loadContent();
}

DateTime::~DateTime()
{}

DateTime::DateTime(DateTime const & src): AMonitorModule(src)
{
	*this = src;
}

DateTime & DateTime::operator=(DateTime const & rhs)
{
	if (this != &rhs)
	{}
	return *this;
}

void			DateTime::loadContent()
{
	time_t		t;
	struct tm	*local;
	char		date[256];

	time(&t);
	local = localtime(&t);
	strftime(date, sizeof(date) - 1, "%a %d %b %G\n%T", local);
	this->_content = std::string(date);

	this->_minWidth = std::strlen(this->_title);
	if (this->_content.length() > this->_minWidth)
		this->_minWidth = this->_content.length();

	this->_minHeigth = 2;
}

std::string		 DateTime::getContent()
{
	DateTime::loadContent();
	return this->_content;
}

const char *	DateTime::getTitle() const
{
	return this->_title;
}

int			DateTime::getMinWidth() const
{
	return this->_minWidth;
}

int			DateTime::getMinHeigth() const
{
	return this->_minHeigth;
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
