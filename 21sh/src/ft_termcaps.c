/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termcaps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 16:46:09 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/06 21:21:42 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <fcntl.h>
#include <sys/ioctl.h>

void				restore_term(void)
{
    tputs(ft_tgetstr("ei"), 1, ft_pchar);
    if ((tcsetattr(data.fd, TCSANOW, &data.old_term)) == -1)
		ft_putendl_fd("Fatal error: tcsetattr() returned.", 2);
}

void				redefine_term(void)
{
    struct termios  termios;

	if (tcgetattr(data.fd, &data.old_term) != 0)
		ft_exit_all("Fatal error: tcgetattr() returned.");
	ft_memcpy(&termios, &data.old_term, sizeof(termios));
	termios.c_lflag &= ~(ICANON | ECHO | ISIG);
	termios.c_cc[VMIN] = 1;
	termios.c_cc[VTIME] = 0;
	if (tcsetattr(data.fd, TCSANOW, &termios) == -1)
		ft_exit_all("Fatal error: tcsetattr() returned.");
	tputs(ft_tgetstr("im"), 1, ft_pchar);
}

void				init_termcaps(char *term_name, int ret)
{
    if (!isatty(STDIN_FILENO))
        ft_exit_all("Terminal not valid.");
    if (!ttyname(STDIN_FILENO))
        ft_exit_all("You are not connected to a terminal.");
    if (ttyslot() <= 0)
        ft_exit_all("No terminal found in databasdata.");
    if ((data.fd = open(ttyname(STDIN_FILENO), O_RDWR)) == -1)
    {
        ft_putstr_fd("Failed to open: ", STDERR_FILENO);
        ft_exit_all(ttyname(STDIN_FILENO));
    }
    if ((term_name = ft_getenv("TERM", data.env)) == NULL)
        term_name = "xterm";
    ret = tgetent(NULL, term_name);
    if (ret == -1)
        ft_exit_all("Termcap's data base files unavailable");
    else if (ret == 0)
        ft_exit_all("Terminal not defined in databasdata.");
	redefine_term();
	if (ioctl(data.fd, TIOCGWINSZ, &data.sz) == -1)
		ft_exit_all("ioctl(TIOCGWINSZ) failed.");
	data.sz.ws_col--;
	data.sz.ws_row--;
}

char				*ft_tgetstr(char *str)
{
	char			*tmp;

	tmp = tgetstr(str, NULL);
	if (!tmp)
	{
		ft_putstr_fd(str, 2);
        ft_putendl_fd(" not available", 2);
    }
    return (tmp);
}

int					ft_pchar(int nb)
{
	return (write(STDIN_FILENO, &nb, 1));
}
