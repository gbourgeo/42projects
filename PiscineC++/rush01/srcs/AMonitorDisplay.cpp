#include <dlfcn.h>
#include "AMonitorDisplay.hpp"

AMonitorDisplay::AMonitorDisplay()
{}

AMonitorDisplay::~AMonitorDisplay()
{
}

AMonitorDisplay::AMonitorDisplay(AMonitorDisplay const & src)
{
	*this = src;
}

AMonitorDisplay & AMonitorDisplay::operator=(AMonitorDisplay const & rhs)
{
	if (this != &rhs) {}
	return *this;
}

void AMonitorDisplay::loadModules(std::string const & path)
{
	_moduleHandler.loadModules(path);
}

IMonitorModule *AMonitorDisplay::getModule(unsigned long idx) const
{
	return this->_moduleHandler.getModule(idx);
}
