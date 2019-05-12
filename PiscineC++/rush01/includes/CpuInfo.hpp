#ifndef CPUINFO_HPP
# define CPUINFO_HPP

# include "IMonitorModule.hpp"

struct 			s_name
{
	const char 	*one;
	const char 	*two;
	int			type;
};

class CpuInfo: public IMonitorModule
{
public:
	CpuInfo();
	~CpuInfo();
	CpuInfo(CpuInfo const & src);
	CpuInfo & operator=(CpuInfo const & rhs);

	void display();

private:
};

#endif
