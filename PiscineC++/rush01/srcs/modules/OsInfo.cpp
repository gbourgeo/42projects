#include <iostream>
#include <cstring>
#include "OsInfo.hpp"

OsInfo::OsInfo()
{
	this->_title = "OS INFO";
	OsInfo::loadContent();
}

OsInfo::~OsInfo()
{}

OsInfo::OsInfo(OsInfo const & src): AMonitorModule(src)
{
	*this = src;
}

OsInfo & OsInfo::operator=(OsInfo const & rhs)
{
	if (this != &rhs)
	{
		this->_os = rhs._os;
	}
	return *this;
}

void				OsInfo::loadContent()
{
	std::string		info;

	uname(&_os);
	this->_minWidth = std::strlen(this->_title);
	info = "Sysname : " + std::string(_os.sysname) + std::string("\n");
	if (info.length() > this->_minWidth)
		this->_minWidth = info.length();
	this->_content = info;
	info = "Nodename: " + std::string(_os.nodename) + std::string("\n");
	if (info.length() > this->_minWidth)
		this->_minWidth = info.length();
	this->_content += info;
	info = "Release : " + std::string(_os.release) + std::string("\n");
	if (info.length() > this->_minWidth)
		this->_minWidth = info.length();
	this->_content += info;
	info = "Version : " + std::string(_os.version) + std::string("\n");
	if (info.length() > this->_minWidth)
		this->_minWidth = info.length();
	this->_content += info;
	info = "Machine : " + std::string(_os.machine);
	if (info.length() > this->_minWidth)
		this->_minWidth = info.length();
	this->_content += info;

	this->_minHeigth = 5;
}

std::string			OsInfo::getContent()
{
	OsInfo::loadContent();
	return this->_content;
}

const char *		OsInfo::getTitle() const
{
	return this->_title;
}

int			OsInfo::getMinWidth() const
{
	return this->_minWidth;
}

int			OsInfo::getMinHeigth() const
{
	return this->_minHeigth;
}

// void OsInfo::display()
// {
// 	std::cout << "OS INFO" << std::endl;
// 	std::cout << "_______" << std::endl;
// 	std::cout << "Sysname : " << _os.sysname << std::endl;
// 	std::cout << "Nodename: " << _os.nodename << std::endl;
// 	std::cout << "Release : " << _os.release << std::endl;
// 	std::cout << "Version : " << _os.version << std::endl;
// 	std::cout << "Machine : " << _os.machine << std::endl;
// }

extern "C"
{
	void *createModule() {
		return reinterpret_cast<void *>(new OsInfo);
	}

	void deleteModule(void *module) {
		delete reinterpret_cast<OsInfo *>(module);
	}
}
