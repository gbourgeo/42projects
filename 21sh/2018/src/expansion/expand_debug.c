/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_debug.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 18:51:53 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/24 19:11:48 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"

#ifndef DEBUG

void			debug_expansion(char *name, t_ret *ret)
{
	(void)name;
	(void)ret;
}

#else

void			debug_expansion(char *name, t_ret *ret)
{
	ft_putstr(name);
	ft_putstr(" word: ");
	ft_putendl(ret->word);
	ft_putstr(name);
	ft_putstr(" subs: ");
	ft_putendl(ret->substitute);
}

#endif
