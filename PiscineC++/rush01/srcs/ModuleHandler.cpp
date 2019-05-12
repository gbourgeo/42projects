#include <iostream>
#include <dirent.h>
#include <dlfcn.h>
#include "ModuleHandler.hpp"

ModuleHandler::ModuleHandler()
{}

ModuleHandler::~ModuleHandler()
{}

ModuleHandler::ModuleHandler(ModuleHandler const & src)
{
	*this = src;
}

ModuleHandler & ModuleHandler::operator=(ModuleHandler const & rhs)
{
	if (this != &rhs) {}
	return *this;
}

void ModuleHandler::loadModules(std::string const &path, std::map<int, void*> &modules, std::map<int, IMonitorModule *> &active)
{
	DIR				*dir;
	struct dirent	*ent;

	dir = opendir(path.c_str());
	if (dir == nullptr) {
		std::cout << "Error opening " << path << "." << std::endl;
		return ;
	}
	while ((ent = readdir(dir)) != nullptr)
	{
		std::string		file(path + std::string("/") + std::string(ent->d_name));

		if (file.find(".so") == std::string::npos)
			continue ;
		std::cout << "Opening module [" << file << "] : ";
		void *module = dlopen(file.c_str(), RTLD_NOW);
		if (module == nullptr) {
			std::cout << dlerror() << std::endl;
			continue ;
		}
		dlerror();
		void *createFunc = dlsym(module, "createModule");
		if (createFunc == nullptr) {
			std::cout << " createModule function not found." <<  std::endl;
			dlclose(module);
			continue ;
		}
		void *deleteFunc = dlsym(module, "deleteModule");
		if (deleteFunc == nullptr) {
			std::cout << " deleteModule function not found." <<  std::endl;
			dlclose(module);
			continue ;
		}
		void *newModule = ((void* (*)())(createFunc))();
		if (newModule == nullptr) {
			std::cout << " can't allocate new module." << std::endl;
			continue ;
		}
		modules.insert(std::make_pair(modules.size(), module));
		active.insert(std::make_pair(active.size(), reinterpret_cast<IMonitorModule *>(newModule)));
		std::cout << "loaded." << std::endl;
	}
}
