#ifndef HOSTNAME_HPP
# define HOSTNAME_HPP

# include <unistd.h>
# include <limits.h>
# include "IMonitorModule.hpp"

class HostName: public IMonitorModule
{
public:
	HostName();
	~HostName();
	HostName(HostName const & src);
	HostName & operator=(HostName const & rhs);

	void display();

private:
	char	_hostname[_SC_HOST_NAME_MAX];
	char	_username[_SC_LOGIN_NAME_MAX];
};

#endif
