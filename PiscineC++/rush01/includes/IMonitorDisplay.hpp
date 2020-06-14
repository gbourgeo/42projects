#ifndef IMONITORDISPLAY
# define IMONITORDISPLAY

# include <string>
# include "IMonitorModule.hpp"

class IMonitorDisplay
{
public:
	virtual ~IMonitorDisplay() {}
	virtual int init() = 0;
	virtual void quit() = 0;
	virtual void loadModules(std::string const &) = 0;
	virtual IMonitorModule *getModule(unsigned long) const = 0;
	virtual void affModule() = 0;
};

#endif
