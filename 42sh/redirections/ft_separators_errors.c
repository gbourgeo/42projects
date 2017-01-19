/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_separators_errors.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/21 02:35:09 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/03/21 02:37:57 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int			ft_check_double_pipe(char **args, int i)
{
	if (i == 0 || ft_strlen(args[i]) > 2)
		return (1);
	if (ft_strcharset(args[i - 1], PIPES) != NULL)
		return (1);
	return (0);
}

int			ft_check_semi_colon(char **args, int i)
{
	if (ft_strlen(args[i]) != 1)
		return (1);
	return (0);
}

int			ft_check_double_and(char **args, int i)
{
	if (i == 0 || ft_strlen(args[i]) > 2)
		return (1);
	if (ft_strcharset(args[i - 1], PIPES) != NULL)
		return (1);
	return (0);
}
