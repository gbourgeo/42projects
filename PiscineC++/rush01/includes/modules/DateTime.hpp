#ifndef DATETIME_HPP
# define DATETIME_HPP

# include <ctime>
# include "IMonitorModule.hpp"

class DateTime: public IMonitorModule
{
public:
	DateTime();
	~DateTime();
	DateTime(DateTime const & src);
	DateTime & operator=(DateTime const & rhs);

	std::string		getTitle() const;
	std::string		getContent() const;
	void			display();

private:
	time_t		_t;
	struct tm	*_local;
	char		_date[256];	
};

#endif
