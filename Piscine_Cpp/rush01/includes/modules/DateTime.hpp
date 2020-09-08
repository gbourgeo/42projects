#ifndef DATETIME_HPP
# define DATETIME_HPP

# include "AMonitorModule.hpp"

# include <ctime>

class DateTime: public AMonitorModule
{
public:
	DateTime();
	~DateTime();
	DateTime(DateTime const & src);
	DateTime & operator=(DateTime const & rhs);

	const char *		getTitle() const;
	std::string			getContent();
	int					getMinWidth() const;
	int					getMinHeigth() const;

private:
	void				loadContent();
};

#endif
