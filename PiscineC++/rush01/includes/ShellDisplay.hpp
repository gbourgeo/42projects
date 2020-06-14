#ifndef SHELLDISPLAY_HPP
# define SHELLDISPLAY_HPP

# include "AMonitorDisplay.hpp"


# include <ncurses.h>
# include <curses.h>
# include <unistd.h>

# define MAINWINSTR		"MainWin"
# define STATUSBARSTR	"StatusBar"

typedef struct	s_win
{
	WINDOW		*win;
	WINDOW		*box;
	int			width;
	int			heigth;
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
	WINDOW			*getWindow(const char *name) const;
	void			affModule();

private:
	void			addWindow(const char * name, t_win &win);
	void			addWindow(std::string name, t_win &win);
	static void		_resizeHandler(int sig);

	std::map<std::string, t_win>	_wins;
};

#endif
