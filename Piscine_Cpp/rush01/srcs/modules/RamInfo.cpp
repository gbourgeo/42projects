#include <iostream>
#include <sys/types.h>
#include <sys/sysctl.h>
#ifdef __APPLE__
# include <mach/mach_host.h>
#endif
#ifdef __linux__
# include <sys/sysinfo.h>
#endif
#include <cstring>
#include "RamInfo.hpp"

RamInfo::RamInfo()
{
	this->_title = "RAM INFO";
	RamInfo::loadContent();
}

RamInfo::~RamInfo()
{}

RamInfo::RamInfo(RamInfo const & src): AMonitorModule(src)
{
	*this = src;
}

RamInfo & RamInfo::operator=(RamInfo const & rhs)
{
	if (this != &rhs)
	{
		this->_mem = rhs._mem;
	}
	return *this;
}

std::string	RamInfo::getContent()
{
	RamInfo::loadContent();
	return this->_content;
}

const char	*RamInfo::getTitle() const
{
	return this->_title;
}

int			RamInfo::getMinWidth() const
{
	return this->_minWidth;
}

int			RamInfo::getMinHeigth() const
{
	return this->_minHeigth;
}

#ifdef __linux__
/*
** struct sysinfo {
**  long uptime;                            // Seconds since boot
**  unsigned long loads[3];                 // 1, 5, and 15 minute load averages
**  unsigned long totalram;                 // Total usable main memory size
**  unsigned long freeram;                  // Available memory size
**  unsigned long sharedram;                // Amount of shared memory
**  unsigned long bufferram;                // Memory used by buffers
**  unsigned long totalswap;                // Total swap space size
**  unsigned long freeswap;                 // Swap space still available
**  unsigned short procs;                   // Number of current processes
**  unsigned long totalhigh;                // Total high memory size
**  unsigned long freehigh;                 // Available high memory size
**  unsigned int mem_unit;                  // Memory unit size in bytes
**  char _f[20-2*sizeof(long)-sizeof(int)]; // Padding to 64 bytes
** };
*/
void		RamInfo::loadContent()
{
	struct sysinfo	info;
	std::string		line;

	errno = 0;
	this->_minHeigth = 1;
	this->_minWidth = std::strlen(this->_title);
	this->_minHeigth = 1;
	if (sysinfo(&info))
	{
		this->_content = std::string(strerror(errno));
		return ;
	}
	line = "Uptime: " + std::to_string(info.uptime) + std::string(" sec\n");
	if (line.length() > this->_minWidth)
		this->_minWidth = line.length();
	this->_content = line;
	line = "Total: " + std::to_string(info.totalram) + std::string("\n");
	if (line.length() > this->_minWidth)
		this->_minWidth = line.length();
	this->_minHeigth++;
	this->_content += line;
	line = "Free: " + std::to_string(info.freeram) + std::string("\n");
	if (line.length() > this->_minWidth)
		this->_minWidth = line.length();
	this->_minHeigth++;
	this->_content += line;
	line = "Shared: " + std::to_string(info.sharedram) + std::string("\n");
	if (line.length() > this->_minWidth)
		this->_minWidth = line.length();
	this->_minHeigth++;
	this->_content += line;
	line = "Buffered: " + std::to_string(info.bufferram) + std::string("\n");
	if (line.length() > this->_minWidth)
		this->_minWidth = line.length();
	this->_minHeigth++;
	this->_content += line;
	line = "Swap Total: " + std::to_string(info.totalswap) + std::string("\n");
	if (line.length() > this->_minWidth)
		this->_minWidth = line.length();
	this->_minHeigth++;
	this->_content += line;
	line = "Swap Free: " + std::to_string(info.freeswap) + std::string("\n");
	if (line.length() > this->_minWidth)
		this->_minWidth = line.length();
	this->_minHeigth++;
	this->_content += line;
	line = "Processes: " + std::to_string(info.procs) + std::string("\n");
	if (line.length() > this->_minWidth)
		this->_minWidth = line.length();
	this->_minHeigth++;
	this->_content += line;
	line = "High Total: " + std::to_string(info.totalhigh) + std::string("\n");
	if (line.length() > this->_minWidth)
		this->_minWidth = line.length();
	this->_minHeigth++;
	this->_content += line;
	line = "High Free: " + std::to_string(info.freehigh) + std::string("\n");
	if (line.length() > this->_minWidth)
		this->_minWidth = line.length();
	this->_minHeigth++;
	this->_content += line;
	line = "Memoy Units Size: " + std::to_string(info.mem_unit) + std::string("\n");
	if (line.length() > this->_minWidth)
		this->_minWidth = line.length();
	this->_minHeigth++;
	this->_content += line;
}
#endif
#ifdef __APPLE__
std::string displayBytes(int64_t data)
{
	const char	*name = "oKGT";
	char		*ptr;
	size_t		size;
	std::string out;

	ptr = const_cast<char *>(name);
	size = 1000;
	while (data / size && *ptr) {
		size *= 1000;
		ptr++;
	}
	return std::string(std::to_string(data / (size / 1000)) + " " + *(ptr - 1) + "o");
}

void RamInfo::loadContent()
{
	struct s_name		names[] = { { "hw.memsize"  , "RAM total", sizeof(int64_t)} };
	struct xsw_usage	swap = {0};
	int 				mib[2];
	int64_t				data;
	size_t				len;

	std::cout << "RAM INFO" << std::endl;
	std::cout << "________" << std::endl;
	// Virtual Memory Stats
//	len = sizeof(swap);
//	if (!sysctlbyname("vm.swapusage", &swap, &len, nullptr, 0)) {
//		std::cout << "Memory total : " << swap.xsu_total << std::endl;
//		std::cout << "Memory avail : " << swap.xsu_avail << std::endl;
//		std::cout << "Memory used : " << swap.xsu_used << std::endl;
//	}
	mib[0] = CTL_HW;
	mib[1] = HW_MEMSIZE;
	len = sizeof(_mem.total);
	sysctl(mib, 2, &_mem.total, &len, nullptr, 0);
	mach_msg_type_number_t count = HOST_VM_INFO_COUNT;
	vm_statistics_data_t vmstat;
	if (KERN_SUCCESS == host_statistics(mach_host_self(), HOST_VM_INFO, (host_info_t)&vmstat, &count)) {
		_mem.avail = (int64_t)vmstat.free_count * (int64_t)swap.xsu_pagesize;
		_mem.used = ((int64_t)vmstat.active_count +
					(int64_t)vmstat.inactive_count +
					(int64_t)vmstat.wire_count) *  (int64_t)swap.xsu_pagesize;
		std::cout << "Memory Total    : " << std::to_string(_mem.total) << std::endl;
		std::cout << "Memory Available: " << std::to_string(_mem.avail) << std::endl;
		std::cout << "Memory Used     : " << std::to_string(_mem.used) << std::endl;
	}
	for (size_t i = 0; i < sizeof(names) / sizeof(*names); i++) {
		data = 0;
		len = names[i].type;
		if (!sysctlbyname(names[i].one, &data, &len, nullptr, 0))
			std::cout << names[i].two << ": " << displayBytes(data) << " (" << std::to_string(data) << " bytes)" << std::endl;
	}
}
#endif

extern "C"
{
	void *createModule() {
		return reinterpret_cast<void *>(new RamInfo);
	}

	void deleteModule(void *module) {
		delete reinterpret_cast<RamInfo *>(module);
	}
}
