#ifndef OSINFO_HPP
# define OSINFO_HPP

# include <sys/utsname.h>
# include "IMonitorModule.hpp"

class OsInfo: public IMonitorModule
{
public:
	OsInfo();
	~OsInfo();
	OsInfo(OsInfo const & src);
	OsInfo & operator=(OsInfo const & rhs);

	std::string		getTitle() const;
	std::string		getContent() const;
	void			display();

private:
	struct utsname	_os;
};

#endif
