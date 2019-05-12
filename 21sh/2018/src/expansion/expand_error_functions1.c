/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_error_functions1.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 22:09:04 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/25 16:01:08 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_dprintf.h"
#include "expansion.h"
#include "expansion_errors.h"

void			err_none_func(t_ret *ret, t_exp *par)
{
	(void)ret;
	(void)par;
	ft_dprintf(STDERR_FILENO, "%s\n", ERR_NONE_STR);
}

void			err_syntax_func(t_ret *ret, t_exp *par)
{
	char		c;

	c = par->buff[par->buff_len];
	((char *)par->buff)[par->buff_len] = '\0';
	(void)ret;
	ft_dprintf(STDERR_FILENO, "%s: %s\n", par->buff, ERR_SYNTAX_STR);
	((char *)par->buff)[par->buff_len] = c;
}

void			err_modifier_func(t_ret *ret, t_exp *par)
{
	(void)ret;
	(void)par;
	ft_dprintf(STDERR_FILENO, "%s\n", ERR_MODIFIER_STR);
}

void			err_unhandled_func(t_ret *ret, t_exp *par)
{
	ft_dprintf(STDERR_FILENO, "`%s': %s %s\n",
		par->buff, ret->word, ERR_UNHANDLED_STR);
}

void			err_malloc_func(t_ret *ret, t_exp *par)
{
	(void)ret;
	(void)par;
	ft_dprintf(STDERR_FILENO, "%s: %s\n", ERR_MALLOC_STR);
}
