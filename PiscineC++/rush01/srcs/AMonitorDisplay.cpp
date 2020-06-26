#include <dlfcn.h>
#include "AMonitorDisplay.hpp"

AMonitorDisplay::AMonitorDisplay()
{}

AMonitorDisplay::~AMonitorDisplay()
{}

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
	this->_moduleHandler.loadModules(path);
}

AMonitorModule *AMonitorDisplay::getModule(size_t idx) const
{
	return this->_moduleHandler.getModule(idx);
}
