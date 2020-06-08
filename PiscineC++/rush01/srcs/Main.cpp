#include "Main.hpp"
#include "ShellDisplay.hpp"
#include "GraphDisplay.hpp"

static int usage(const char *prog)
{
	std::cerr << "Usage:\t" << prog << " [" << OPT_TERM << " " << OPT_GRAPH << "] [module path]" << std::endl;
	std::cerr << "\t" << OPT_TERM << "\t\tTerminal view." << std::endl;
	std::cerr << "\t" << OPT_GRAPH << "\t\tGraphical view." << std::endl;
	std::cerr << "\t[module path]\tAbsolute path of modules." << std::endl;
	return 1;
}

int		main(int ac, char **av)
{
	std::string		flag;
	std::string		path;
	AMonitorDisplay	*display;

	if (ac != 3)
		return usage(av[0]);
	av++;
	flag = (**av == '-') ? std::string(*av) : std::string(*(av + 1));
	path = (**av == '-') ? std::string(*(av + 1)) : std::string(*av);
	display = nullptr;
	if (!flag.compare(OPT_TERM))
		display = new ShellDisplay();
	else if (!flag.compare(OPT_GRAPH))
		display = new GraphDisplay();
	else
		return usage(av[-1]);
//	display->init();
	display->loadModules(path);
	for (unsigned long i = 0; display->getModule(i); i++) {
		std::cout << std::endl;
		display->getModule(i)->display();
	}
		if (display)
		delete display;
	return 0;
}
