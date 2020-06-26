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
	ShellDisplay();
	~ShellDisplay();
	ShellDisplay(ShellDisplay const & src);
	ShellDisplay & operator=(ShellDisplay const & rhs);

	int				init();
	void			quit();
	void			loadModules(std::string const & modulePath);
	int				affModules() const;
	int				getLineMaxHeigth(int line) const;

private:
	void			addWindow(const char * name, t_win &win);
	static void		_resizeHandler(int sig);

	std::map<std::string, t_win>	_wins;
};

#endif
