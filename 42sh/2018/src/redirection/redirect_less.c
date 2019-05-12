/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_less.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 07:28:57 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/22 14:38:01 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "redirection.h"

int				redirect_less(t_redirection **redir, t_s_env *e)
{
	(*redir)->fdio = (*redir)->ionumber ? ft_atoi((*redir)->ionumber->head) : 0;
	if (((*redir)->fdarg = open((*redir)->arg->cmd[0], O_RDONLY)) < 0)
		return (redirect_open_error((*redir)->arg->cmd[0], e));
	return (0);
}
