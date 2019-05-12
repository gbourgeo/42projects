/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 00:59:23 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/29 16:47:04 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "redirection.h"
#include "redirection_errors.h"
#include "operator_types.h"

int				redirection(t_redirection **redir, t_s_env *e)
{
	static int		(*handler[])(t_redirection **, t_s_env *) = {
		redirect_less, redirect_less_and, redirect_less_great, redirect_great,
		redirect_great_pipe, redirect_and_great, redirect_great_and,
		redirect_dgreat, redirect_and_dgreat, redirect_dless,
	};
	char			*token;

	if (!(*redir) || !(*redir)->arg || !(*redir)->token)
		return (0);
	(*redir)->fdio = -1;
	(*redir)->fdarg = -1;
	if (!(*redir)->arg->cmd || !(*redir)->arg->cmd[0])
	{
		token = ft_strndup((char *)(*redir)->arg->token->head,
						(*redir)->arg->token->len);
		redirect_error(ERR_AMBIGUOUS, token, e);
		free(token);
		return (1);
	}
	return (handler[(*redir)->token->id - LESS_VALUE](redir, e));
}
