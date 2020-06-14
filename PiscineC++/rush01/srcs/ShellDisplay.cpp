#include <iostream>
#include <dirent.h>
#include <dlfcn.h>
#include <signal.h>
#include <string.h>
#include "ShellDisplay.hpp"

ShellDisplay::ShellDisplay()
{}

ShellDisplay::~ShellDisplay()
{
	ShellDisplay::quit();
}

ShellDisplay::ShellDisplay(ShellDisplay const & src)
{
	*this = src;
}

ShellDisplay & ShellDisplay::operator=(ShellDisplay const & rhs)
{
	if (this != &rhs) {}
	return *this;
}

int ShellDisplay::init()
{
	t_win		win;

	memset(&win, 0, sizeof(win));
	signal(SIGWINCH, ShellDisplay::_resizeHandler);
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
	getmaxyx(win.win, win.width, win.heigth);
	ShellDisplay::addWindow(STATUSBARSTR, win);
	return (1);
}

void ShellDisplay::quit()
{
	std::map<std::string, t_win>::iterator	itr;

	itr = this->_wins.begin();
	itr++;
	while (itr != this->_wins.end())
	{
		if (itr->second.win)
			delwin(itr->second.win);
		if (itr->second.box)
			delwin(itr->second.box);
		itr++;
	}
	endwin();
}

void ShellDisplay::loadModules(std::string const & modulePath)
{
	t_win			win;
	unsigned long	i;

	AMonitorDisplay::loadModules(modulePath);
	for (i = 0; AMonitorDisplay::getModule(i); i++)
	{
		memset(&win, 0, sizeof(win));
		auto module = AMonitorDisplay::getModule(i);
		ShellDisplay::addWindow(module->getTitle(), win);
	}
	wprintw(this->_wins.find(STATUSBARSTR)->second.win, "Module loaded: %ld ", i);
	wrefresh(this->_wins.find(STATUSBARSTR)->second.win);
}

WINDOW *ShellDisplay::getWindow(const char *name) const
{
	auto itr = this->_wins.find(std::string(name));
	if (itr != this->_wins.end())
		return (itr->second.win);
	wprintw(this->_wins.find(std::string(MAINWINSTR))->second.win, "getWindow failed");
	wrefresh(this->_wins.find(std::string(MAINWINSTR))->second.win);
	return nullptr;
}

void			ShellDisplay::affModule()
{
	IMonitorModule	*module;
	std::string		title;
	unsigned long	i;
	int				colon;
	int				line;
	t_win			mainWin;

	i = 0;
	colon = 0;
	line = 0;
	mainWin = this->_wins.find(std::string(MAINWINSTR))->second;
	if (mainWin.width < 3)
		return ;
	while ((module = AMonitorDisplay::getModule(i)) != nullptr)
	{
		title = module->getTitle();
		auto ptr = this->_wins.find(title);
		if (ptr != this->_wins.end())
		{
			if (colon + (int)title.length() + 2 > mainWin.width)
			{
				colon = 0;
				line++;
			}
			if (line * 10 > mainWin.heigth)
				break ;
			if (ptr->second.win == nullptr)
			{
				ptr->second.box = subwin(mainWin.win, 10, title.length() + 2, line, colon);
				box(ptr->second.box, 0, 0);
				mvwaddstr(ptr->second.box, 0, 1, title.c_str());
				wrefresh(ptr->second.box);
				ptr->second.win = subwin(ptr->second.box, 9, 9, line + 1, colon + 1);
				getmaxyx(ptr->second.box, ptr->second.width, ptr->second.heigth);
			}
			colon += title.length() + 2;
		}
		i++;
	}
}

//
//	Private Methodes
//

void ShellDisplay::addWindow(const char *name, t_win &win)
{
	this->_wins.insert(std::pair<std::string, t_win>(std::string(name), win));
}

void ShellDisplay::addWindow(std::string name, t_win &win)
{
	this->_wins.insert(std::pair<std::string, t_win>(name, win));
}

void ShellDisplay::_resizeHandler(int sig)
{
	clear();
	mvprintw(0,0,"SIGNAL ENCOUTERED : %d", sig);
	if (sig == 28)
		mvprintw(3,0,"Resizing window is not allowed");
	refresh();
	sleep(2);
	endwin();
	exit(0);
}
