#include <dlfcn.h>
#include "AMonitorDisplay.hpp"

AMonitorDisplay::AMonitorDisplay():
	_moduleHandler(nullptr)
{}

AMonitorDisplay::AMonitorDisplay(std::string const & modulePath)
{
	this->_moduleHandler = new ModuleHandler(modulePath);
}

AMonitorDisplay::~AMonitorDisplay()
{
	if (this->_moduleHandler)
		delete this->_moduleHandler;
	this->_moduleHandler = nullptr;
}

AMonitorDisplay::AMonitorDisplay(AMonitorDisplay const & src)
{
	*this = src;
}

AMonitorDisplay & AMonitorDisplay::operator=(AMonitorDisplay const & rhs)
{
	if (this != &rhs) {
		if (this->_moduleHandler)
			delete this->_moduleHandler;
		this->_moduleHandler = new ModuleHandler(rhs.getModulePath());
	}
	return *this;
}

std::string AMonitorDisplay::getModulePath() const
{
	return this->_moduleHandler->getModulePath();
}

AMonitorModule *AMonitorDisplay::getModule(size_t idx) const
{
	return this->_moduleHandler->getModule(idx);
}
