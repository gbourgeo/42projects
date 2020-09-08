#ifndef HOSTNAME_HPP
# define HOSTNAME_HPP

# include "AMonitorModule.hpp"

# include <limits.h>
# include <unistd.h>

class HostName: public AMonitorModule
{
public:
	HostName();
	~HostName();
	HostName(HostName const & src);
	HostName & operator=(HostName const & rhs);

	const char *		getTitle() const;
	std::string			getContent();
	int					getMinWidth() const;
	int					getMinHeigth() const;

private:
	void				loadContent();
};

#endif
