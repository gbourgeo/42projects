#include <iostream>
#include <dirent.h>
#include <dlfcn.h>
#include "ModuleHandler.hpp"

ModuleHandler::ModuleHandler()
{}

ModuleHandler::ModuleHandler(std::string const & modulePath)
{
	DIR				*dir;
	struct dirent	*ent;
	t_module		mod;

	if (modulePath.empty() == true)
		return ;
	dir = opendir(modulePath.c_str());
	if (dir == nullptr) {
		return ;
	}
	while ((ent = readdir(dir)) != nullptr)
	{
		std::string		file(modulePath + std::string("/") + std::string(ent->d_name));

		if (file.find(".so") == std::string::npos)
			continue ;
		mod.modulePtr = dlopen(file.c_str(), RTLD_LAZY | RTLD_GLOBAL);
		if (mod.modulePtr == nullptr) {
			continue ;
		}
		// reset errors
		dlerror();
		void *createFunc = dlsym(mod.modulePtr, "createModule");
		if (createFunc == nullptr) {
			dlclose(mod.modulePtr);
			continue ;
		}
		void *deleteFunc = dlsym(mod.modulePtr, "deleteModule");
		if (deleteFunc == nullptr) {
			dlclose(mod.modulePtr);
			continue ;
		}
		void *newModule = ((void* (*)())(createFunc))();
		if (newModule == nullptr) {
			continue ;
		}
		mod.moduleClss = reinterpret_cast<AMonitorModule *>(newModule);
		mod.deleteFunc = deleteFunc;
		this->_modules.insert(std::pair<std::string, t_module>(file, mod));
	}
	closedir(dir);
	this->_modulesPath = modulePath;
}

ModuleHandler::~ModuleHandler()
{
	std::map<std::string, t_module>::iterator	it;

	this->_modulesPath.clear();
	for (it = _modules.begin(); it != _modules.end(); it++)
	{
		if (it->second.deleteFunc) {
			((void (*)(void *))(it->second.deleteFunc))(reinterpret_cast<void *>(it->second.moduleClss));
		}
		if (it->second.modulePtr)
			dlclose(it->second.modulePtr);
	}
	this->_modules.clear();
}

ModuleHandler::ModuleHandler(ModuleHandler const & src)
{
	*this = src;
}

ModuleHandler & ModuleHandler::operator=(ModuleHandler const & rhs)
{
	if (this != &rhs) {}
	return *this;
}

std::string		ModuleHandler::getModulePath() const
{
	return this->_modulesPath;
}

AMonitorModule *ModuleHandler::getModule(size_t idx) const
{
	size_t										i;
	std::map<std::string, t_module>::const_iterator	itr;

	if (idx >= this->_modules.size())
		return nullptr;
	i = 0;
	itr = this->_modules.begin();
	while (i++ < idx)
		itr++;
	return itr->second.moduleClss;
}

int ModuleHandler::getSize() const
{
	return this->_modules.size();
}
