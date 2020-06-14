#ifndef RAMINFO_HPP
# define RAMINFO_HPP

# include <string>
# include "IMonitorModule.hpp"

struct 			s_name
{
	const char 	*one;
	const char 	*two;
	int			type;
};

class RamInfo: public IMonitorModule
{
public:
	RamInfo();
	~RamInfo();
	RamInfo(RamInfo const & src);
	RamInfo & operator=(RamInfo const & rhs);

	std::string		getTitle() const;
	std::string		getContent() const;
	void			display();

private:
    std::string displayBytes(int64_t) const;

	struct MemoryStat {
		unsigned long long  total;
		unsigned long long  avail;
		unsigned long long  used;
		unsigned long long  app;
	};

	struct MemoryStat	_mem;
};


#endif
