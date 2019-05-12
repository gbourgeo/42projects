#include <dlfcn.h>
#include "AMonitorDisplay.hpp"

AMonitorDisplay::AMonitorDisplay()
{}

AMonitorDisplay::~AMonitorDisplay()
{
	std::map<int, void *>::iterator				it;
	std::map<int, IMonitorModule *>::iterator	it2;

	it2 = _active.begin();
	for (it = _modules.begin(); it != _modules.end(); it++)
	{
		void *deleteFunc = dlsym(it->second, "deleteModule");
		if (deleteFunc) {
			((void (*)(void *))(deleteFunc))(reinterpret_cast<void *>(it2->second));
		}
		it2++;
		dlclose(it->second);
	}
	_modules.clear();
	_active.clear();
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
	_moduleHandler.loadModules(path, _modules, _active);
}

IMonitorModule *AMonitorDisplay::getModule(unsigned long idx) const
{
	if (idx < _active.size())
		return _active.at(idx);
	return nullptr;
}
