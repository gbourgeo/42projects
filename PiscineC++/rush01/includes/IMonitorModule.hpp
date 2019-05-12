#ifndef IMONITORMODULE_HPP
# define IMONITORMODULE_HPP

class IMonitorModule
{
public:
	virtual ~IMonitorModule() {}
	// virtual void *createModule() = 0;
	// virtual void deleteModule(void *) = 0;
	virtual void display() = 0;
};

#endif
