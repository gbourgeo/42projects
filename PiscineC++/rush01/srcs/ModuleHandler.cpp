#include <iostream>
#include <dirent.h>
#include <dlfcn.h>
#include "ModuleHandler.hpp"

ModuleHandler::ModuleHandler()
{}

ModuleHandler::~ModuleHandler()
{
	std::map<std::string, t_module>::iterator	it;

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

#include<fstream>

void ModuleHandler::loadModules(std::string const & path)
{
	DIR				*dir;
	struct dirent	*ent;
	t_module		mod;

	if (path.empty() == true)
		return ;
std::ofstream f(".logs", std::ios_base::trunc | std::ios::out);
	dir = opendir(path.c_str());
	if (dir == nullptr) {
f << "Error opening " << path << "." << std::endl;
		return ;
	}
	while ((ent = readdir(dir)) != nullptr)
	{
		std::string		file(path + std::string("/") + std::string(ent->d_name));

		if (file.find(".so") == std::string::npos)
			continue ;
		f << "file: " << file << " opened:\n\t";
		mod.modulePtr = dlopen(file.c_str(), RTLD_LAZY | RTLD_GLOBAL);
		if (mod.modulePtr == nullptr) {
			f << "dlopen: " << dlerror() << std::endl;
			continue ;
		}
		// reset errors
		dlerror();
		void *createFunc = dlsym(mod.modulePtr, "createModule");
		if (createFunc == nullptr) {
			f << "dlsym: createModule function not found." <<  std::endl;
			dlclose(mod.modulePtr);
			continue ;
		}
		void *deleteFunc = dlsym(mod.modulePtr, "deleteModule");
		if (deleteFunc == nullptr) {
			f << "dlsym: deleteModule function not found." <<  std::endl;
			dlclose(mod.modulePtr);
			continue ;
		}
		void *newModule = ((void* (*)())(createFunc))();
		if (newModule == nullptr) {
			f << "ERROR: can't allocate new module." << std::endl;
			continue ;
		}
		f << "OK" << std::endl;
		mod.moduleClss = reinterpret_cast<AMonitorModule *>(newModule);
		mod.deleteFunc = deleteFunc;
		this->_modules.insert(std::pair<std::string, t_module>(file, mod));
	}
f.close();
	closedir(dir);
	this->_modulesPath = path;
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
