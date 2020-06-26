#ifndef RAMINFO_HPP
# define RAMINFO_HPP

# include "AMonitorModule.hpp"

class RamInfo: public AMonitorModule
{
public:
	RamInfo();
	~RamInfo();
	RamInfo(RamInfo const & src);
	RamInfo & operator=(RamInfo const & rhs);

	const char *		getTitle() const;
	std::string			getContent();
	int					getMinWidth() const;
	int					getMinHeigth() const;

private:
	void				loadContent();

	struct MemoryStat {
		unsigned long long	total;
		unsigned long long	avail;
		unsigned long long	used;
		unsigned long long	app;
	};

	struct MemoryStat	_mem;
};


#endif
