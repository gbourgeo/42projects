/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 04:47:21 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/23 05:38:10 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static int		ft_minishell(int fd, char **environ)
{
	t_env		e;
	char		*buf;
	int			ret;

	ret = 0;
	if (init_shell(fd, &e, environ))
	{
		prompt(e.env);
		if ((buf = ft_strnew(READ_SIZE + 1)) == NULL)
			ft_error("42sh: Malloc error, unabled to continue...", &e);
		tputs(ft_tgetstr("sc"), 1, ft_pchar);
		while ((ret = read(e.fd, buf, READ_SIZE)) > 0)
		{
			read_command(buf, &e);
			ft_strclr(buf);
		}
	}
	return (ret);
}

static int		ft_minishell_file(char **av, char **environ)
{
	t_env		e;
	int			ret;
	int			fd;

	if (!(ret = access(av[1], R_OK)))
	{
		fd = ft_open(av[1], O_RDONLY, 0644);
		if (ft_dup2(fd, 0) >= 0 && init_shell(fd, &e, environ))
		{
			while ((ret = get_next_line(e.fd, &e.history->command)) > 0)
			{
				if (ft_strstr("exit", e.history->command))
					break ;
				ft_parser(&e);
				free(e.history->command);
				if (!e.status)
					break ;
			}
		}
		ft_close(fd);
		free(e.history->command);
		return (e.status);
	}
	ft_strerror(ft_strjoin("42sh: Unable to access :", av[1]));
	return (ret);
}

int				main(int ac, char **av)
{
	extern char	**environ;

	if (ac > 1)
		return (ft_minishell_file(av, environ));
	else
		return (ft_minishell(0, environ));
	return (0);
}
