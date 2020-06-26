#ifndef MODULEHANDLER_HPP
# define MODULEHANDLER_HPP

# include "AMonitorModule.hpp"

# include <string>
# include <map>

typedef struct	s_module
{
	void			*modulePtr;
	AMonitorModule	*moduleClss;
	void			*deleteFunc;
}				t_module;

class ModuleHandler
{
public:
	ModuleHandler();
	~ModuleHandler();
	ModuleHandler(ModuleHandler const & src);
	ModuleHandler & operator=(ModuleHandler const & rhs);

	void			loadModules(std::string const &);
	AMonitorModule	*getModule(size_t) const;
	int				getSize(void) const;

private:
	std::map<std::string, t_module>	_modules;
	std::string						_modulesPath;
};

#endif
