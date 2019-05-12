/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 18:24:38 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/22 02:07:56 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

void			free_quote(t_quote **quote)
{
	if (*quote == NULLQUOTE)
		return ;
	free_quote(&(*quote)->next);
	free(*quote);
	*quote = NULLQUOTE;
}

void			free_token(t_token **token)
{
	if (*token == NULLTOKEN)
		return ;
	free_token(&(*token)->next);
	free_quote(&(*token)->quote);
	if ((*token)->hdocfree)
		free((void *)(*token)->hdocline);
	free(*token);
	*token = NULLTOKEN;
}

void			free_hdoc(t_hdoc **hdoc)
{
	if (!*hdoc)
		return ;
	free_hdoc(&(*hdoc)->next);
	free(*hdoc);
	*hdoc = NULLHDOC;
}
