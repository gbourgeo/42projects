/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termcaps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 10:28:23 by naminei           #+#    #+#             */
/*   Updated: 2019/08/02 22:41:34 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alcu.h"

static int	ft_pchar(int nb)
{
	return (write(STDIN_FILENO, &nb, 1));
}

int			ft_tputs(char *str)
{
	char	*tmp;

	tmp = tgetstr(str, NULL);
	if (!tmp)
	{
		ft_putstr_fd(str, 2);
		ft_putendl_fd(" not available", 2);
		return (1);
	}
	tputs(tmp, 1, ft_pchar);
	return (0);
}

int			ft_tgetent(char *term)
{
	int		ret;

	ret = tgetent(NULL, term);
	if (!term)
	{
		ft_putendl_fd("TERM not set (see 'env')", 2);
		return (1);
	}
	if (ret != 1)
	{
		ft_putstr_fd("Database for '", 2);
		ft_putstr_fd(term, 2);
		ft_putendl_fd("' is not available.", 2);
		return (1);
	}
	return (0);
}
