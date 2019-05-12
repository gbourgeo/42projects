#ifndef MODULEHANDLER_HPP
# define MODULEHANDLER_HPP

# include <string>
# include <map>
# include "IMonitorModule.hpp"

class ModuleHandler
{
public:
	ModuleHandler();
	~ModuleHandler();
	ModuleHandler(ModuleHandler const & src);
	ModuleHandler & operator=(ModuleHandler const & rhs);

	void		loadModules(std::string const &, std::map<int, void *> &, std::map<int, IMonitorModule *> &);
};

#endif
