#include <iostream>
#include <dirent.h>
#include <dlfcn.h>
#include "ShellDisplay.hpp"

ShellDisplay::ShellDisplay()
{}

ShellDisplay::~ShellDisplay()
{}

ShellDisplay::ShellDisplay(ShellDisplay const & src)
{
	*this = src;
}

ShellDisplay & ShellDisplay::operator=(ShellDisplay const & rhs)
{
	if (this != &rhs) {}
	return *this;
}

void ShellDisplay::init()
{
	signal(SIGWINCH, ShellDisplay::_resizeHandler);
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	getmaxyx(stdscr, _maxH, _maxW);

	start_color();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_GREEN, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_BLUE, COLOR_BLACK);
	refresh();
	_win = NULL;
}

//
//	Private Methodes
//

void ShellDisplay::_resizeHandler(int sig)
{
	clear();
	mvprintw(0,0,"SIGNAL ENCOUTERED : %d", sig);
	if (sig == 28)
		mvprintw(3,0,"Resizing window is not allowed");
	refresh();
	sleep(2);
	exit(0);
}
