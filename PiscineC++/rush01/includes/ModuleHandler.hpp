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
	ModuleHandler(std::string const & modulePath);
	~ModuleHandler();
	ModuleHandler(ModuleHandler const & src);
	ModuleHandler & operator=(ModuleHandler const & rhs);

	std::string		getModulePath() const;
	AMonitorModule	*getModule(size_t) const;
	int				getSize(void) const;

private:
	ModuleHandler();

	std::string						_modulesPath;
	std::map<std::string, t_module>	_modules;
};

#endif
