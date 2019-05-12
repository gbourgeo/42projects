/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_properties.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 03:54:40 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/26 18:33:39 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include "libft.h"
#include "shell_term.h"
#include "shell.h"

void		term_restore(struct termios *save)
{
	t_line	*line;

	if (tcsetattr(0, TCSANOW, save) == -1)
	{
		ft_putendl("Fatal error: unable to restore the term attributes.");
		exit(2);
	}
	line = get_struct();
	reset_signal(line->signals);
}

void		define_new_term(struct termios *save)
{
	struct termios	termios;
	t_line			*line;

	if (tcgetattr(0, save) != 0)
	{
		ft_putendl("Fatal error: unable to get term attributes.");
		exit(2);
	}
	ft_memcpy(&termios, save, sizeof(termios));
	termios.c_lflag &= ~(ICANON | ECHO | ISIG);
	termios.c_cc[VMIN] = 1;
	termios.c_cc[VTIME] = 1;
	if ((tcsetattr(0, TCSANOW, &termios)) == -1)
	{
		ft_putendl("Fatal error: unable to set the new term attributes.");
		exit(2);
	}
	line = get_struct();
	set_signal(line->signals);
}
