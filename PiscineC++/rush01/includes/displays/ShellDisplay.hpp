#ifndef SHELLDISPLAY_HPP
# define SHELLDISPLAY_HPP

# include "AMonitorDisplay.hpp"

# include <ncurses.h>
# include <curses.h>
# include <unistd.h>
# include <map>

# define MAINWINSTR		"MainWin"
# define STATUSBARSTR	"StatusBar"

typedef struct	s_win
{
	WINDOW			*box;
	int				width;
	int				heigth;
	WINDOW			*win;
	int				posX;
	int				posY;
	AMonitorModule	*module;
}				t_win;

class ShellDisplay: public AMonitorDisplay
{
public:
	ShellDisplay(std::string const & modulePath);
	~ShellDisplay();
	ShellDisplay(ShellDisplay const & src);
	ShellDisplay & operator=(ShellDisplay const & rhs);

	void			start() const;

	int				initTerminalNcurses();
	void			quit();
	int				loadModules();

private:
	ShellDisplay();
	void			addWindow(const char * name, t_win &win);
	int				getLineMaxHeigth(int line) const;
	static void		_resizeHandler(int sig);

	std::map<std::string, t_win>	_wins;
};

#endif
