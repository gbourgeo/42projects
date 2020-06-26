#include "Main.hpp"
#include "ShellDisplay.hpp"
#include "GraphDisplay.hpp"

static int		usage(const char *prog, t_opt opts[], size_t size)
{
	std::cerr << "Usage:\t" << prog;
	for (size_t i = 0; i < size; i++)
	{
		if (opts[i].name.empty() != true)
			std::cerr << " [" << opts[i].name << "]";
	}
	std::cerr << std::endl;
	for (size_t i = 0; i < size; i++)
	{
		std::cerr << "\t" << opts[i].name;
		if (opts[i].name.length() < 8)
			std::cerr << "\t\t";
		else
			std::cerr << "\t";
		std::cerr << opts[i].description << "." << std::endl;
	}
	return (1);
}

static int		get_args(char **av, t_opt opts[], size_t size, t_arg *args)
{
	args->view = 0;
	args->libpath.clear();
	for (int i = 1; av[i]; i++)
	{
		if (av[i][0] == '-')
		{
			if (args->view != 0)
			{
				std::cerr << av[0] << ": Parameter already given (" << av[i] << ")." << std::endl;
				return (0);
			}
			for (size_t j = 0; j < size; j++)
			{
				if (opts[j].name.compare(av[i]) == 0)
				{
					args->view = opts[j].value;
					break ;
				}
			}
			if (args->view == 0)
			{
				std::cerr << av[0] << ": Wrong Parameter (" << av[i] << ")." << std::endl;
				return (0);
			}
		}
		else
		{
			if (args->libpath.empty() != true)
			{
				std::cerr << av[0] << ": Too many argument (" << av[i];
				std::cerr << "). Path already set: " << args->libpath;
				std::cerr << "." << std::endl;
				return (0);
			}
			args->libpath = std::string(av[i]);
		}
	}
	if (args->view == 0 || args->libpath.empty() == true)
	{
		std::cerr << av[0] << ": Missing parameter." << std::endl;
		return (0);
	}
	return (1);
}

int		main(int ac, char **av)
{
	static t_opt	opts[] = {
		{ "-t", "Terminal view", (1 << 0) },
		{ "-g", "Graphical view", (1 << 1) },
		{ "module_dir", "Path to module directory", -1 },
	};
	size_t			optsSize;
	t_arg			args;
	AMonitorDisplay	*display;

	optsSize = sizeof(opts) / sizeof(opts[0]);
	if (ac < 3)
		return usage(av[0], opts, optsSize);
	display = nullptr;
	if (!get_args(av, opts, optsSize, &args))
		return (1);
	if (args.view == (1 << 0))
		display = new ShellDisplay();
	else if (args.view == (1 << 1))
		display = new GraphDisplay();
	if (!display)
		return (2);
	if (!display->init())
		return (3);
	display->loadModules(args.libpath);
	while (1)
	{
		if (!display->affModules())
			break ;
	}
	delete display;
	return 0;
}
