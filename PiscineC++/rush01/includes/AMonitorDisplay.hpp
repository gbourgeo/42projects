#ifndef AMONITORDISPLAY_HPP
# define AMONITORDISPLAY_HPP

# include "IMonitorDisplay.hpp"
# include "ModuleHandler.hpp"

class AMonitorDisplay: public IMonitorDisplay
{
public:
	AMonitorDisplay();
	~AMonitorDisplay();
	AMonitorDisplay(AMonitorDisplay const & src);
	AMonitorDisplay & operator=(AMonitorDisplay const & rhs);

	virtual int				init() = 0;
	virtual void			quit() = 0;
	virtual void			loadModules(std::string const & modulePath);
	virtual AMonitorModule	*getModule(size_t idx) const;
	virtual int				affModules() const = 0;

protected:
	ModuleHandler					_moduleHandler;
};

#endif
