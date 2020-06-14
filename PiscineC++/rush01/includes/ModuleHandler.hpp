#ifndef MODULEHANDLER_HPP
# define MODULEHANDLER_HPP

# include <string>
# include <map>
# include "IMonitorModule.hpp"

typedef struct	s_module
{
	void			*modulePtr;
	IMonitorModule	*moduleClss;
}				t_module;

class ModuleHandler
{
public:
	ModuleHandler();
	~ModuleHandler();
	ModuleHandler(ModuleHandler const & src);
	ModuleHandler & operator=(ModuleHandler const & rhs);

	void			loadModules(std::string const &);
	IMonitorModule	*getModule(unsigned long idx) const;

private:
	std::map<int, t_module>			_modules;
};

#endif
