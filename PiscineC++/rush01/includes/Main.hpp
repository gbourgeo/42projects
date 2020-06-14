
#ifndef MAIN_HPP
# define MAIN_HPP

# include <iostream>

typedef struct		s_opt
{
	std::string		name;
	std::string		description;
	int				value;
}					t_opt;

typedef struct		s_arg
{
	int				view;
	std::string		libpath;
}					t_arg;

void		terminal_viewer();
void		graphical_viewer();

#endif
