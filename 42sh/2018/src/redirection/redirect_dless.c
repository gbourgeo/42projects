/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_dless.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 07:21:59 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/29 13:31:18 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_dprintf.h"
#include "parser.h"
#include "redirection.h"
#include "struct.h"
#include "redirection_errors.h"
#include "main_tools.h"
#include "shell.h"

static int		handle_here_doc(t_redirection **redir, t_s_env *e)
{
	static size_t	fnum = 0;
	int				mode;
	t_token			*operator;

	mode = O_CREAT | O_TRUNC | O_WRONLY;
	if (!((*redir)->file = ft_strjoinfree(SHELL_TMP_FILE,
											ft_itoa(fnum++), 2)))
		return (redirect_error(ERR_MALLOC, (*redir)->arg->cmd[0], e));
	if (((*redir)->fdarg = open((*redir)->file, mode, 0600)) < 0)
		return (redirect_open_error((*redir)->file, e));
	operator = (*redir)->token;
	if (operator->hdocline)
	{
		write((*redir)->fdarg, operator->hdocline, operator->hdoclen);
		if (operator->hdocline[operator->hdoclen - 1] != '\n')
			write((*redir)->fdarg, "\n", 1);
	}
	return (0);
}

int				redirect_dless(t_redirection **redir, t_s_env *e)
{
	(*redir)->fdio = (*redir)->ionumber ? ft_atoi((*redir)->ionumber->head) : 0;
	if (handle_here_doc(redir, e))
		return (1);
	if (((*redir)->fdarg = open((*redir)->file, O_RDONLY)) < 0)
		return (redirect_open_error((*redir)->file, e));
	return (0);
}
