#ifndef IMONITORDISPLAY
# define IMONITORDISPLAY

# include <string>
# include "AMonitorModule.hpp"

class IMonitorDisplay
{
public:
	virtual ~IMonitorDisplay() {}
	virtual int init() = 0;
	virtual void quit() = 0;
	virtual void loadModules(std::string const &) = 0;
	virtual AMonitorModule *getModule(unsigned long) const = 0;
	virtual int affModules() const = 0;
};

#endif
