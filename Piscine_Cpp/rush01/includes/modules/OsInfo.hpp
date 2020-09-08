#ifndef OSINFO_HPP
# define OSINFO_HPP

# include "AMonitorModule.hpp"

# include <sys/utsname.h>

class OsInfo: public AMonitorModule
{
public:
	OsInfo();
	~OsInfo();
	OsInfo(OsInfo const & src);
	OsInfo & operator=(OsInfo const & rhs);

	const char *		getTitle() const;
	std::string			getContent();
	int					getMinWidth() const;
	int					getMinHeigth() const;

private:
	void				loadContent();

	struct utsname	_os;
};

#endif
