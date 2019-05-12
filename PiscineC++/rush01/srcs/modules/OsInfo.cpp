#include <iostream>
#include "OsInfo.hpp"

OsInfo::OsInfo()
{
	uname(&_os);
}

OsInfo::~OsInfo()
{}

OsInfo::OsInfo(OsInfo const & src)
{
	*this = src;
}

OsInfo & OsInfo::operator=(OsInfo const & rhs)
{
	return *this;
}

void OsInfo::display()
{
	std::cout << "OS INFO" << std::endl;
	std::cout << "_______" << std::endl;
	std::cout << "Sysname : " << _os.sysname << std::endl;
	std::cout << "Nodename: " << _os.nodename << std::endl;
	std::cout << "Release : " << _os.release << std::endl;
	std::cout << "Version : " << _os.version << std::endl;
	std::cout << "Machine : " << _os.machine << std::endl;
}

extern "C"
{
	void *createModule() {
		return reinterpret_cast<void *>(new OsInfo);
	}

	void deleteModule(void *module) {
		delete reinterpret_cast<OsInfo *>(module);
	}
}
