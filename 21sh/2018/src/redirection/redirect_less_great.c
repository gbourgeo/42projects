/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_less_great.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 07:28:05 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/24 07:38:52 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "redirection.h"

int				redirect_less_great(t_redirection **redir, t_s_env *e)
{
	(*redir)->fdio = 0;
	if ((*redir)->ionumber)
		(*redir)->fdio = ft_atoi((*redir)->ionumber->head);
	(*redir)->fdarg = open((*redir)->arg->cmd[0], O_CREAT | O_RDWR, 0644);
	if ((*redir)->fdarg < 0)
		return (redirect_open_error((*redir)->arg->cmd[0], e));
	return (0);
}
