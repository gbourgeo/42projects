#ifndef SHELLDISPLAY_HPP
# define SHELLDISPLAY_HPP

# include "AMonitorDisplay.hpp"


# include <ncurses.h>
# include <curses.h>
# include <unistd.h>

class ShellDisplay: public AMonitorDisplay
{
public:
	ShellDisplay();
	~ShellDisplay();
	ShellDisplay(ShellDisplay const & src);
	ShellDisplay & operator=(ShellDisplay const & rhs);

	void			init();
	void 			Display();

private:
	static void _resizeHandler(int sig);
	WINDOW *_win;
	int _maxW;
	int _maxH;
};

#endif
