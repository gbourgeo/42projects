/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_error_functions2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 22:09:45 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/28 21:58:43 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_dprintf.h"
#include "expansion.h"
#include "expansion_errors.h"

void			err_directory_func(t_ret *ret, t_exp *par)
{
	(void)ret;
	(void)par;
	ft_dprintf(STDERR_FILENO, "%s\n", ERR_DIRECTORY_STACK_STR);
}

void			err_given_func(t_ret *ret, t_exp *par)
{
	(void)par;
	ft_dprintf(STDERR_FILENO, "%s: %s\n",
	ret->word + 1 + ret->brace + ret->hash, ret->substitute);
}

void			err_no_user_func(t_ret *ret, t_exp *par)
{
	(void)par;
	ft_dprintf(STDERR_FILENO, "%s %s\n",
		ERR_NO_SUCH_USER_STR, ret ? ret->word : "");
}

void			err_ambigous_func(t_ret *ret, t_exp *par)
{
	(void)par;
	ft_dprintf(STDERR_FILENO, "%s: %s\n",
		ret ? ret->substitute : "", ERR_AMBIGUOUS_STR);
}
