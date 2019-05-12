#include <iostream>
#include "HostName.hpp"

HostName::HostName()
{
	gethostname(_hostname, _SC_HOST_NAME_MAX);
	getlogin_r(_username, _SC_LOGIN_NAME_MAX);
}

HostName::~HostName()
{}

HostName::HostName(HostName const & src)
{
	*this = src;
}

HostName & HostName::operator=(HostName const & rhs)
{
	return *this;
}

void HostName::display()
{
	std::cout << "HOSTNAME | USERNAME" << std::endl;
	std::cout << "___________________" << std::endl;
	std::cout << _hostname << " | " << _username << std::endl;
}

extern "C"
{
	void *createModule() {
		return reinterpret_cast<void *>(new HostName);
	}

	void deleteModule(void *module) {
		delete reinterpret_cast<HostName *>(module);
	}
}
