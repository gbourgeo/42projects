/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_great_and.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 07:25:09 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/23 18:31:01 by gbourgeo         ###   ########.fr       */
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

/*
** Lines of code for bash 5.0.7 compliance :
** -> can not overwrite existing file.
**
** static int		check_access(char *cmd)
** {
** return (cmd[0] == '/' || access(cmd, F_OK));
** }
**
** else if (!check_access((*redir)->arg->cmd[0]))
** return (redirect_error(ERR_EXISTING, (*redir)->arg->cmd[0], e));
*/

int				redirect_great_and(t_redirection **redir, t_s_env *e)
{
	ssize_t		i;
	int			mode;

	mode = O_CREAT | O_TRUNC | O_WRONLY;
	(*redir)->fdio = (*redir)->ionumber ? ft_atoi((*redir)->ionumber->head) : 1;
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
	else if ((*redir)->fdio != 1)
		return (redirect_error(ERR_AMBIGUOUS, (*redir)->arg->cmd[0], e));
	else if (((*redir)->fdarg = open((*redir)->arg->cmd[0], mode, 0644)) < 0)
		return (redirect_open_error((*redir)->arg->cmd[0], e));
	if (fcntl(GET_FD((*redir)->fdarg), F_GETFD) < 0)
		return (redirect_error(ERR_BAD_FD, (*redir)->arg->cmd[0], e));
	return (0);
}
