#include <iostream>
#include <dirent.h>
#include <dlfcn.h>
#include <signal.h>
#include <string.h>
#include <sstream>
#include <csignal>
#include <mutex>
#include "ShellDisplay.hpp"

static ShellDisplay		*g_instance = nullptr;
static std::mutex		g_lock;

ShellDisplay::ShellDisplay()
{}

ShellDisplay::ShellDisplay(std::string const & modulePath):
	AMonitorDisplay(modulePath)
{
	g_instance = this;
	std::signal(SIGWINCH, ShellDisplay::_resizeHandler);
	if (!ShellDisplay::initTerminalNcurses() || !ShellDisplay::loadModules())
		ShellDisplay::quit();
}

ShellDisplay::~ShellDisplay()
{
	ShellDisplay::quit();
}

ShellDisplay::ShellDisplay(ShellDisplay const & src):
	AMonitorDisplay(src.getModulePath())
{
	*this = src;
}

ShellDisplay & ShellDisplay::operator=(ShellDisplay const & rhs)
{
	if (this != &rhs) {
		g_instance = this;
		std::signal(SIGWINCH, ShellDisplay::_resizeHandler);
		if (!ShellDisplay::initTerminalNcurses() || !ShellDisplay::loadModules())
			ShellDisplay::quit();
	}
	return *this;
}

int ShellDisplay::initTerminalNcurses()
{
	t_win		win;

	memset(&win, 0, sizeof(win));
	win.win = initscr();
	if (!win.win)
		return (0);
	cbreak();
	noecho();
	curs_set(0);
	keypad(win.win, TRUE);
	nodelay(win.win, TRUE);
	getmaxyx(win.win, win.heigth, win.width);

	start_color();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_GREEN, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_BLUE, COLOR_BLACK);
	refresh();
	ShellDisplay::addWindow(MAINWINSTR, win);
	win.win = subwin(win.win, 1, win.width, win.heigth - 1, 0);
	if (!win.win)
		return (0);
	getmaxyx(win.win, win.heigth, win.width);
	win.posY = win.heigth - 1;
	ShellDisplay::addWindow(STATUSBARSTR, win);
	return (1);
}

void ShellDisplay::quit()
{
	std::map<std::string, t_win>::iterator	itr;

	for (itr = this->_wins.begin();
		itr != this->_wins.end(); itr++)
	{
		if (itr->first.compare(MAINWINSTR) == 0)
			continue ;
		if (itr->second.win)
		{
			wclear(itr->second.win);
			wrefresh(itr->second.win);
			delwin(itr->second.win);
		}
		if (itr->second.box)
		{
			wclear(itr->second.box);
			wrefresh(itr->second.box);
			delwin(itr->second.box);
		}
	}
	clear();
	refresh();
	endwin();
	this->_wins.clear();
}

int ShellDisplay::loadModules()
{
	std::map<std::string, t_win>::iterator		mainWin;
	t_win		win;
	int			colon;
	int			line;

	mainWin = this->_wins.find(std::string(MAINWINSTR));
	if (this->_moduleHandler == nullptr || mainWin == this->_wins.end())
		return 0;
	memset(&win, 0, sizeof(win));
	colon = line = 0;
	for (int i = 0; i < this->_moduleHandler->getSize(); i++)
	{
		if ((win.module = this->_moduleHandler->getModule(i)) == nullptr)
			continue ;
		if (colon + win.module->getMinWidth() + 2 >= mainWin->second.width)
		{
			colon = 0;
			line += ShellDisplay::getLineMaxHeigth(line);
		}
		if (this->_wins.find(win.module->getTitle()) == this->_wins.end())
		{
			win.box = subwin(mainWin->second.win,
				win.module->getMinHeigth() + 2,
				win.module->getMinWidth() + 2,
				line,
				colon);
			getmaxyx(win.box, win.heigth, win.width);
			win.win = subwin(win.box,
				win.module->getMinHeigth(),
				win.module->getMinWidth(),
				line + 1,
				colon + 1);
		}
		win.posX = colon;
		win.posY = line;
		ShellDisplay::addWindow(win.module->getTitle(), win);
		colon += win.module->getMinWidth() + 2;
	}
	return 1;
}

void		ShellDisplay::start() const
{
	std::map<std::string, t_win>::const_iterator	itr;
	size_t			moduleAffCount;
	useconds_t		refreshRate;
	int				ch;

	refreshRate = 100000;
	while (1)
	{
		if (this->_moduleHandler == nullptr)
			break ;
		if (g_lock.try_lock() == false)
			continue ;
		itr = this->_wins.find(std::string(MAINWINSTR));
		if (itr == this->_wins.end())
			break ; // Shall i retry to init() ?
		ch = wgetch(itr->second.win);
		if (ch == 27) // ESC character
			break ;
		if (ch == 43 && refreshRate < 5000000) // KB_PLUS, 5000000 = 5 seconds
			refreshRate += 100000;
		if (ch == 45 && refreshRate > 0) // KB_MINUS
			refreshRate -= 100000;
		moduleAffCount = 0;
		if (itr->second.width > 3 && itr->second.heigth > 3)
		{
			usleep(refreshRate);
			for (auto itr2 = this->_wins.begin(); itr2 != this->_wins.end(); itr2++)
			{
				if (itr2->first.compare(MAINWINSTR) == 0
					|| itr2->first.compare(STATUSBARSTR) == 0)
					continue;
				wclear(itr2->second.win);
				wclear(itr2->second.box);
				if (itr2->second.posY + itr2->second.heigth < LINES
					|| itr2->second.posX + itr2->second.width <= COLS)
				{
					box(itr2->second.box, 0, 0);
					mvwaddstr(itr2->second.box, 0, 1, itr2->second.module->getTitle());
					wrefresh(itr2->second.box);

					std::istringstream ss(itr2->second.module->getContent());
					std::string line;
					int lines = 0;
					while (std::getline(ss, line))
						mvwaddstr(itr2->second.win, lines++, 0, line.c_str());
					moduleAffCount++;
				}
				wrefresh(itr2->second.box);
				wrefresh(itr2->second.win);
			}
		}
		itr = this->_wins.find(std::string(STATUSBARSTR));
		if (itr != this->_wins.end())
		{
			wclear(itr->second.win);
			wprintw(itr->second.win, "Modules loaded: %ld/%ld RefreshRate: %ldms",
				moduleAffCount, this->_moduleHandler->getSize(), refreshRate);
			wrefresh(itr->second.win);
		}
		g_lock.unlock();
	}
	g_lock.unlock();
}

//
//	Private Methodes
//
#include <cstring>

void ShellDisplay::addWindow(const char *name, t_win &win)
{
	auto ret = this->_wins.insert(std::pair<std::string, t_win>(std::string(name), win));
	if (ret.second == false)
		std::memcpy(&this->_wins.at(std::string(name)), &win, sizeof(t_win));
		// this->_wins.at(std::string(name)) = win;
}

int ShellDisplay::getLineMaxHeigth(int line) const
{
	int		heigth = 0;

	auto ptr = this->_wins.begin();
	while (ptr != this->_wins.end())
	{
		if (ptr->first.compare(MAINWINSTR) != 0
		 && ptr->first.compare(STATUSBARSTR) != 0
		 && ptr->second.posY == line)
		{
			if (heigth < ptr->second.heigth)
				heigth = ptr->second.heigth;
		}
		ptr++;
	}
	return heigth;
}

void ShellDisplay::_resizeHandler(int sig)
{
	int				colon;
	int				line;

	(void)sig;
	colon = 0;
	line = 0;
	if (!g_instance)
		return ;
	g_lock.lock();
	g_instance->quit();
	g_instance->initTerminalNcurses();
	g_instance->loadModules();
	usleep(100000);
	g_lock.unlock();
}
