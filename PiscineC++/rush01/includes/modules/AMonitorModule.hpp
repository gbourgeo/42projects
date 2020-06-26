#ifndef AMONITORMODULE_HPP
# define AMONITORMODULE_HPP

# include "IMonitorModule.hpp"

class AMonitorModule: public IMonitorModule
{
public:
	AMonitorModule() = default;
	virtual ~AMonitorModule() = default;
	AMonitorModule(AMonitorModule const & src);
	AMonitorModule & operator=(AMonitorModule const & rhs);

	virtual const char *	getTitle() const = 0;
	virtual std::string		getContent() = 0;
	virtual int				getMinWidth() const = 0;
	virtual int				getMinHeigth() const = 0;

protected:
	virtual void			loadContent() = 0;

	const char			*_title;
	std::string			_content;
	int					_minWidth;
	int					_minHeigth;
	int					_posX;
	int					_posY;
};

#endif
