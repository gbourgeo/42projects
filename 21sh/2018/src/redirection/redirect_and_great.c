/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_and_great.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 07:26:06 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/16 20:12:54 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "redirection.h"
#include "redirection_errors.h"

int				redirect_and_great(t_redirection **redir, t_s_env *e)
{
	t_redirection	*next;
	int				mode;

	mode = O_CREAT | O_TRUNC | O_WRONLY;
	(*redir)->fdio = 1;
	if (((*redir)->fdarg = open((*redir)->arg->cmd[0], mode, 0644)) < 0)
		return (redirect_open_error((*redir)->arg->cmd[0], e));
	next = (*redir)->next;
	if (!((*redir)->next = ft_memalloc(sizeof(*(*redir)->next))))
		return (redirect_error(ERR_MALLOC, (*redir)->arg->cmd[0], e));
	(*redir)->next->fdio = 2;
	(*redir)->next->fdarg = (*redir)->fdarg;
	(*redir)->next->next = next;
	*redir = (*redir)->next;
	return (0);
}
