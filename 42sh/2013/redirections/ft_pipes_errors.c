/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/06 13:15:35 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/03/27 08:00:17 by gsaynac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int			ft_check_redirect_left(char **args, int i)
{
	if (ft_strlen(args[i]) == 1)
	{
		if (ft_strcharset(args[i + 1], PIPES) != NULL || args[i + 1] == '\0')
			return (1);
	}
	else if (ft_strlen(args[i]) >= 2)
		return (1);
	return (0);
}

int			ft_check_redirect_right(char **args, int i)
{
	if ((args[i + 1]) && !ft_strcharset(args[i + 1], "<>|&;"))
	{
		if (ft_strlen(args[i]) == 1)
			return (0);
		else if (ft_strlen(args[i]) == 2)
		{
			if (args[i][1] == '>')
				return (0);
		}
	}
	return (1);
}

int			ft_check_redirect_pipe(char **args, int i)
{
	if (i == 0)
		return (1);
	if (ft_strcharset(args[i - 1], "<>|&;"))
		return (1);
	if (!args[i + 1] || ft_strcharset(args[i + 1], "<>|&;"))
		return (1);
	return (0);
}
