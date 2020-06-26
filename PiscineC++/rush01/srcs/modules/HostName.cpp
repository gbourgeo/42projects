#include <iostream>
#include <cstring>
#include "HostName.hpp"

HostName::HostName()
{
	this->_title = "HOSTNAME | USERNAME";
	HostName::loadContent();
}

HostName::~HostName()
{}

HostName::HostName(HostName const & src): AMonitorModule(src)
{
	*this = src;
}

HostName & HostName::operator=(HostName const & rhs)
{
	if (this != &rhs)
	{}
	return *this;
}

void			HostName::loadContent()
{
	char			_hostname[_SC_HOST_NAME_MAX];
	char			_username[_SC_LOGIN_NAME_MAX];

	gethostname(_hostname, _SC_HOST_NAME_MAX);
	getlogin_r(_username, _SC_LOGIN_NAME_MAX);

	this->_content = std::string(_hostname)
		+ std::string("\n")
		+ std::string(_username);

	this->_minWidth = std::strlen(this->_title);
	if (std::strlen(_hostname) > this->_minWidth)
		this->_minWidth = std::strlen(_hostname);
	if (std::strlen(_username) > this->_minWidth)
		this->_minWidth = std::strlen(_username);

	this->_minHeigth = 2;
}

std::string		HostName::getContent()
{
	HostName::loadContent();
	return this->_content;
}

const char *	HostName::getTitle() const
{
	return this->_title;
}

int			HostName::getMinWidth() const
{
	return this->_minWidth;
}

int			HostName::getMinHeigth() const
{
	return this->_minHeigth;
}

// void HostName::display()
// {
// 	std::cout << "HOSTNAME | USERNAME" << std::endl;
// 	std::cout << "___________________" << std::endl;
// 	std::cout << _hostname << " | " << _username << std::endl;
// }

extern "C"
{
	void *createModule() {
		return reinterpret_cast<void *>(new HostName);
	}

	void deleteModule(void *module) {
		delete reinterpret_cast<HostName *>(module);
	}
}
