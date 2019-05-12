/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_addchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 23:59:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/14 01:32:57 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"
#include "expansion_errors.h"

static int	param_error(char *save, t_ret *ret)
{
	if (save)
		free(save);
	if (ret->substitute)
		free(ret->substitute);
	ft_memset(ret, 0, sizeof(*ret));
	return (ERR_MALLOC);
}

int			param_addchar(char c, t_ret *ret)
{
	char	*save;

	save = NULL;
	if (ret->w_len == ret->w_max)
	{
		save = ret->word;
		ret->w_max += RET_CHUNK;
		if (!(ret->word = ft_memalloc(ret->w_max + 1)))
			return (param_error(save, ret));
	}
	if (save)
		ft_strcpy(ret->word, save);
	ret->word[ret->w_len++] = c;
	if (save)
		free(save);
	return (ERR_NONE);
}
