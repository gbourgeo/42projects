#ifndef IMONITORDISPLAY
# define IMONITORDISPLAY

class IMonitorDisplay
{
public:
	virtual ~IMonitorDisplay() {}
	virtual void start() const = 0;
};

#endif
