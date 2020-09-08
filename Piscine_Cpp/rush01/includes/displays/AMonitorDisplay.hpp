#ifndef AMONITORDISPLAY_HPP
# define AMONITORDISPLAY_HPP

# include "IMonitorDisplay.hpp"
# include "ModuleHandler.hpp"

class AMonitorDisplay: public IMonitorDisplay
{
public:
	AMonitorDisplay(std::string const & modulePath);
	~AMonitorDisplay();
	AMonitorDisplay(AMonitorDisplay const & src);
	AMonitorDisplay & operator=(AMonitorDisplay const & rhs);

	virtual void		start() const = 0;

protected:
	AMonitorDisplay();
	std::string			getModulePath() const;
	AMonitorModule		*getModule(size_t idx) const;

	ModuleHandler		*_moduleHandler;
};

#endif
