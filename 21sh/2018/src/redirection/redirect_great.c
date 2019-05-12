/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_great.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 07:27:38 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/13 18:50:34 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "redirection.h"
#include "redirection_errors.h"

int				redirect_great(t_redirection **redir, t_s_env *e)
{
	int			mode;

	mode = O_CREAT | O_TRUNC | O_WRONLY;
	(*redir)->fdio = (*redir)->ionumber ? ft_atoi((*redir)->ionumber->head) : 1;
	if (access((*redir)->arg->cmd[0], F_OK) == 0)
		return (redirect_error(ERR_EXISTING, (*redir)->arg->cmd[0], e));
	if (((*redir)->fdarg = open((*redir)->arg->cmd[0], mode, 0644)) < 0)
		return (redirect_open_error((*redir)->arg->cmd[0], e));
	return (0);
}
