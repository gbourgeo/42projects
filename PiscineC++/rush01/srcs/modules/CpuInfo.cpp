#include <iostream>
#include <sys/types.h>
#include <sys/sysctl.h> // OSX
#include <stdint.h> // uint32_t type
#include "CpuInfo.hpp"

CpuInfo::CpuInfo()
{}

CpuInfo::~CpuInfo()
{}

CpuInfo::CpuInfo(CpuInfo const & src)
{
	*this = src;
}

CpuInfo & CpuInfo::operator=(CpuInfo const & rhs)
{
	if (this != &rhs)
	{}
	return *this;
}

void CpuInfo::display()
{
	char			str[256];
	struct s_name	name[] = { { "hw.activecpu"                     , "Active CPU            ", sizeof(int32_t) },
						  	  { "hw.cpu64bit_capable"               , "64bit capable         ", sizeof(int32_t) },
							  { "hw.cpufamily"                      , "Family                ", sizeof(int32_t) },
							  { "hw.cpufrequency"                   , "Frequency             ", sizeof(int64_t) },
							  { "hw.cpufrequency_max"               , "Frequency Max         ", sizeof(int64_t) },
							  { "hw.cpufrequency_min"               , "Frequency Min         ", sizeof(int64_t) },
							  { "hw.cpusubtype"                     , "Subtype               ", sizeof(int32_t) },
							  { "hw.cputhreadtype"                  , "Thread Type           ", sizeof(int32_t) },
							  { "hw.cputype"                      	, "Type                  ", sizeof(int32_t) },
							  { "hw.logicalcpu"                     , "Logical CPU           ", sizeof(int32_t) },
							  { "hw.logicalcpu_max"                 , "Logical CPU Max       ", sizeof(int32_t) },
							  { "hw.physicalcpu"                    , "Physical CPU          ", sizeof(int32_t) },
							  { "hw.physicalcpu_max"                , "Physical CPU Max      ", sizeof(int32_t) },
							  { "hw.clockrate"                      , "Clock Rate            ", sizeof(int32_t) },
							  { "machdep.cpu.address_bits.physical" , "Addr. Physical        ", sizeof(int32_t) },
							  { "machdep.cpu.address_bits.virtual"  , "Addr. Virtual         ", sizeof(int32_t) },
//							  { "machdep.cpu.brand"                 , "Brand                 ", sizeof(int32_t) },
							  { "machdep.cpu.brand_string"          , "Brand name            ", sizeof(str) },
							  { "machdep.cpu.cache.L2_associativity", "Cache L2 associativity", sizeof(int32_t) },
							  { "machdep.cpu.cache.linesize"        , "Cache line size       ", sizeof(int32_t) },
							  { "machdep.cpu.cache.size"            , "Cache size            ", sizeof(int32_t) },
							  { "machdep.cpu.core_count"            , "Core Count            ", sizeof(int32_t) },
							  { "machdep.cpu.cores_per_package"     , "Core per Package      ", sizeof(int32_t) },
							  { "machdep.cpu.extfamily"             , "Ext. family           ", sizeof(int32_t) },
							  { "machdep.cpu.extfeature_bits"       , "Ext. feature bits     ", sizeof(int64_t) },
							  { "machdep.cpu.extfeatures"           , "Ext. features         ", sizeof(str) },
							  { "machdep.cpu.extmodel"              , "Ext. model            ", sizeof(int32_t) },
							  { "machdep.cpu.family"                , "Family                ", sizeof(int32_t) },
							  { "machdep.cpu.feature_bits"          , "Feature bits          ", sizeof(int64_t) },
							  { "machdep.cpu.features"              , "Features              ", sizeof(str) },
							  { "machdep.cpu.leaf7_feature_bits"    , "Leaf7 features bits   ", sizeof(uint32_t) },
							  { "machdep.cpu.leaf7_features"        , "Leaf7 features        ", sizeof(str) },
							  { "machdep.cpu.logical_per_package"   , "Logical per package   ", sizeof(int32_t) },
							  { "machdep.cpu.max_basic"             , "Max basic             ", sizeof(uint32_t) },
							  { "machdep.cpu.max_ext"               , "Max ext               ", sizeof(uint32_t) },
							  { "machdep.cpu.microcode_version"     , "Microcode version     ", sizeof(int32_t) },
							  { "machdep.cpu.model"                 , "Model                 ", sizeof(int32_t) },
							  { "machdep.cpu.processor_flag"        , "Processor flag        ", sizeof(int32_t) },
							  { "machdep.cpu.signature"             , "Signature             ", sizeof(int32_t) },
							  { "machdep.cpu.stepping"              , "Stepping              ", sizeof(int32_t) },
							  { "machdep.cpu.thread_count"          , "Thread count          ", sizeof(int32_t) },
							  { "machdep.cpu.tlb.data.large"        , "TLB data large        ", sizeof(int32_t) },
							  { "machdep.cpu.tlb.data.large_level1" , "TLB data large lvl1   ", sizeof(int32_t) },
							  { "machdep.cpu.tlb.data.small"        , "TLB data small        ", sizeof(int32_t) },
							  { "machdep.cpu.tlb.data.small_level1" , "TLB data small lvl1   ", sizeof(int32_t) },
							  { "machdep.cpu.tlb.inst.large"        , "TLB inst large        ", sizeof(int32_t) },
							  { "machdep.cpu.tlb.inst.small"        , "TLB inst small        ", sizeof(int32_t) },
							  { "machdep.cpu.tlb.shared"            , "TLB shared            ", sizeof(int32_t) },
							  { "machdep.cpu.ucupdate"              , "Uc update             ", sizeof(int32_t) }, 
							  { "machdep.cpu.vendor"                , "Vendor                ", sizeof(str) },
							  { "machdep.cpu.xsave.extended_state"  , "Xsave extended state  ", sizeof(uint32_t) },
//							  { "machdep.tsc.deep_idle_rebase"      , "" }, 
//							  { "machdep.tsc.frequency"             , "" },
//							  { "machdep.tsc.nanotime.generation"   , "" },
//							  { "machdep.tsc.nanotime.shift"        , "" },
							  };
	int64_t	store;
	size_t	len;

	std::cout << "CPU Info" << std::endl;
	std::cout << "________" << std::endl;
	for (size_t i = 0; i < sizeof(name) / sizeof(*name); i++) {
		store = 0;
		len = name[i].type;
		if (len == sizeof(str)) {
#ifdef __APPLE__
			if (!sysctlbyname(name[i].one, &str, &len, nullptr, 0))
				std::cout << name[i].two << ": " << str << std::endl;
		} else if (!sysctlbyname(name[i].one, &store, &len, nullptr, 0)) 
			std::cout << name[i].two << ": " << std::to_string(store) << std::endl;
#endif
		}
	}
}

extern "C"
{
	void *createModule() {
		return reinterpret_cast<void *>(new CpuInfo);
	}

	void deleteModule(void *module) {
		delete reinterpret_cast<CpuInfo *>(module);
	}
}
