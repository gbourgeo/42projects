/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_error_functions3.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 15:26:50 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/16 21:01:13 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_dprintf.h"
#include "expansion.h"
#include "expansion_errors.h"

void			err_pipe_func(t_ret *ret, t_exp *par)
{
	(void)ret;
	(void)par;
	ft_dprintf(STDERR_FILENO, "%s\n", ERR_PIPE_STR);
}

void			err_fcntl_func(t_ret *ret, t_exp *par)
{
	(void)ret;
	(void)par;
	ft_dprintf(STDERR_FILENO, "%s\n", ERR_FCNTL_STR);
}

void			err_fork_func(t_ret *ret, t_exp *par)
{
	(void)ret;
	(void)par;
	ft_dprintf(STDERR_FILENO, "%s\n", ERR_FORK_STR);
}

void			err_no_match_func(t_ret *ret, t_exp *par)
{
	(void)par;
	ft_dprintf(STDERR_FILENO, "%s: %s\n", ERR_NO_MATCH_FOUND_STR, ret->word);
}
