#ifndef IMONITORMODULE_HPP
# define IMONITORMODULE_HPP

# include <string>

class IMonitorModule
{
public:
	virtual ~IMonitorModule() {}
	virtual const char *	getTitle() const = 0;
	virtual std::string		getContent() = 0;
	virtual int				getMinWidth() const = 0;
	virtual int				getMinHeigth() const = 0;

protected:
	virtual void			loadContent() = 0;
};

#endif
