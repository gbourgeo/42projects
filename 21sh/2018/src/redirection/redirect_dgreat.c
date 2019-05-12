/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_dgreat.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 07:24:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/29 16:33:31 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "redirection.h"

int				redirect_dgreat(t_redirection **redir, t_s_env *e)
{
	int			mode;

	mode = O_CREAT | O_APPEND | O_WRONLY;
	if ((*redir)->ionumber)
		(*redir)->fdio = ft_atoi((*redir)->ionumber->head);
	else
		(*redir)->fdio = 1;
	if (((*redir)->fdarg = open((*redir)->arg->cmd[0], mode, 0644)) < 0)
		return (redirect_open_error((*redir)->arg->cmd[0], e));
	return (0);
}
