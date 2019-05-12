#ifndef IMONITORDISPLAY
# define IMONITORDISPLAY

# include <string>
# include "IMonitorModule.hpp"

class IMonitorDisplay
{
public:
	virtual ~IMonitorDisplay() {}
	virtual void init() = 0;
	virtual void loadModules(std::string const &) = 0;
	virtual IMonitorModule *getModule(unsigned long) const = 0;
};

#endif
