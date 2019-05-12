/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_less_and.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 07:28:32 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/13 18:24:37 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "redirection.h"
#include "redirection_errors.h"

static ssize_t	is_a_file_descriptor(char *arg)
{
	ssize_t		i;

	i = 0;
	while (arg[i] && ft_isdigit(arg[i]))
		i++;
	if (!arg[i] || !ft_strcmp(&arg[i], "-"))
		return (i);
	return (-1);
}

int				redirect_less_and(t_redirection **redir, t_s_env *e)
{
	ssize_t		i;

	(*redir)->fdio = 0;
	if ((*redir)->ionumber)
		(*redir)->fdio = ft_atoi((*redir)->ionumber->head);
	if (!ft_strcmp((*redir)->arg->cmd[0], "-"))
	{
		(*redir)->fdio |= CLOSE_FD_ON_EXEC;
		return (0);
	}
	if ((i = is_a_file_descriptor((*redir)->arg->cmd[0])) >= 0)
	{
		(*redir)->fdarg = ft_atoi((*redir)->arg->cmd[0]);
		if ((*redir)->arg->cmd[0][i] == '-')
			(*redir)->fdarg |= CLOSE_FD_ON_EXEC;
	}
	else
		return (redirect_error(ERR_AMBIGUOUS, (*redir)->arg->cmd[0], e));
	if (fcntl(GET_FD((*redir)->fdarg), F_GETFD) < 0)
		return (redirect_error(ERR_BAD_FD, (*redir)->arg->cmd[0], e));
	return (0);
}
