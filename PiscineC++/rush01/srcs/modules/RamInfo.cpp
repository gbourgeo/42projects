#include <iostream>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <mach/mach_host.h>
#include "RamInfo.hpp"

RamInfo::RamInfo()
{
}

RamInfo::~RamInfo()
{}

RamInfo::RamInfo(RamInfo const & src)
{
	*this = src;
}

RamInfo & RamInfo::operator=(RamInfo const & rhs)
{
	return *this;
}

std::string RamInfo::displayBytes(int64_t data) const
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

void RamInfo::display()
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

extern "C"
{
	void *createModule() {
		return reinterpret_cast<void *>(new RamInfo);
	}

	void deleteModule(void *module) {
		delete reinterpret_cast<RamInfo *>(module);
	}
}
