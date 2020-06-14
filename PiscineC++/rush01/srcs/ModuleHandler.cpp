#include <iostream>
#include <dirent.h>
#include <dlfcn.h>
#include "ModuleHandler.hpp"

ModuleHandler::ModuleHandler()
{}

ModuleHandler::~ModuleHandler()
{
	std::map<int, t_module>::iterator	it;

	for (it = _modules.begin(); it != _modules.end(); it++)
	{
		void *deleteFunc = dlsym(it->second.modulePtr, "deleteModule");
		if (deleteFunc) {
			((void (*)(void *))(deleteFunc))(reinterpret_cast<void *>(it->second.moduleClss));
		}
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

void ModuleHandler::loadModules(std::string const &path)
{
	DIR				*dir;
	struct dirent	*ent;
	t_module		mod;

	dir = opendir(path.c_str());
	if (dir == nullptr) {
		// std::cout << "Error opening " << path << "." << std::endl;
		return ;
	}
	while ((ent = readdir(dir)) != nullptr)
	{
		std::string		file(path + std::string("/") + std::string(ent->d_name));

		if (file.find(".so") == std::string::npos)
			continue ;
		mod.modulePtr = dlopen(file.c_str(), RTLD_NOW);
		if (mod.modulePtr == nullptr) {
			// std::cout << dlerror() << std::endl;
			continue ;
		}
		void *createFunc = dlsym(mod.modulePtr, "createModule");
		if (createFunc == nullptr) {
			// std::cout << " createModule function not found." <<  std::endl;
			dlclose(mod.modulePtr);
			continue ;
		}
		void *deleteFunc = dlsym(mod.modulePtr, "deleteModule");
		if (deleteFunc == nullptr) {
			// std::cout << " deleteModule function not found." <<  std::endl;
			dlclose(mod.modulePtr);
			continue ;
		}
		void *newModule = ((void* (*)())(createFunc))();
		if (newModule == nullptr) {
			// std::cout << " can't allocate new module." << std::endl;
			continue ;
		}
		mod.moduleClss = reinterpret_cast<IMonitorModule *>(newModule);
		this->_modules.insert(std::make_pair(this->_modules.size(), mod));
	}
	closedir(dir);
}

IMonitorModule *ModuleHandler::getModule(unsigned long idx) const
{
	if (idx < this->_modules.size())
		return this->_modules.at(idx).moduleClss;
	return nullptr;
}