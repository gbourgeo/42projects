/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_analysis_.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/06 11:22:07 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/03/27 19:59:14 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static int	ft_parse_error(char *args)
{
	ft_putstr("42sh: parse error near `");
	ft_putstr(args);
	ft_putendl("'");
	return (1);
}

static int	ft_pipes_analysis(char **args)
{
	int		i;

	i = 0;
	if (args == NULL)
		return (1);
	while (args[i] != '\0')
	{
		if (ft_strchr(PIPES, args[i][0]) != NULL)
		{
			if (ft_strlen(args[i]) > 4)
				return (ft_parse_error(args[i]));
			else if (args[i][0] == '<' && ft_check_redirect_left(args, i))
				return (ft_parse_error(args[i]));
			else if (args[i][0] == '>' && ft_check_redirect_right(args, i))
				return (ft_parse_error(args[i]));
			else if (args[i][0] == '|' && ft_check_redirect_pipe(args, i))
				return (ft_parse_error(args[i]));
		}
		i++;
	}
	return (0);
}

int			ft_syntax_analysis(char **args)
{
	int		i;

	i = 0;
	if (args == NULL)
		return (1);
	while (args[i] != '\0')
	{
		if (ft_strchr(SEPARATORS, args[i][0]) != NULL)
		{
			if (ft_strlen(args[i]) > 2)
				return (ft_parse_error(args[i]));
			if (ft_strstr(args[i], "||") && ft_check_double_pipe(args, i))
				return (ft_parse_error(args[i]));
			else if (ft_strchr(args[i], ';') && ft_check_semi_colon(args, i))
				return (ft_parse_error(args[i]));
			else if (ft_strstr(args[i], "&&") && ft_check_double_and(args, i))
				return (ft_parse_error(args[i]));
		}
		i++;
	}
	return (ft_pipes_analysis(args));
}
