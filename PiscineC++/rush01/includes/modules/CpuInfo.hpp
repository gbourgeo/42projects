#ifndef CPUINFO_HPP
# define CPUINFO_HPP

# include "AMonitorModule.hpp"

class CpuInfo: public AMonitorModule
{
public:
	CpuInfo();
	~CpuInfo();
	CpuInfo(CpuInfo const & src);
	CpuInfo & operator=(CpuInfo const & rhs);

	const char *		getTitle() const;
	std::string			getContent();
	int					getMinWidth() const;
	int					getMinHeigth() const;

private:
	void				loadContent();
};

#endif
