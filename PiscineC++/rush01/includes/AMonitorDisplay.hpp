#ifndef AMONITORDISPLAY_HPP
# define AMONITORDISPLAY_HPP

# include <map>

# include "IMonitorDisplay.hpp"
# include "IMonitorModule.hpp"
# include "ModuleHandler.hpp"

class AMonitorDisplay: public IMonitorDisplay
{
public:
	AMonitorDisplay();
	~AMonitorDisplay();
	AMonitorDisplay(AMonitorDisplay const & src);
	AMonitorDisplay & operator=(AMonitorDisplay const & rhs);

	virtual void			init() = 0;
	virtual void			loadModules(std::string const & modulePath);
	virtual IMonitorModule	*getModule(unsigned long idx) const;

protected:
	ModuleHandler					_moduleHandler;
	std::map<int, void *>			_modules;
	std::map<int, IMonitorModule *>	_active;
};

#endif
