/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_free_t_ret.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 18:56:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/02 20:38:05 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"

void			expand_free_t_ret(t_ret *ret, int free_ret)
{
	if (!ret)
		return ;
	expand_free_t_ret(ret->next, 1);
	if (ret->word)
		free(ret->word);
	if (ret->substitute && ret->freeable)
		free(ret->substitute);
	ft_memset(ret, 0, sizeof(*ret));
	if (free_ret)
		free(ret);
}
