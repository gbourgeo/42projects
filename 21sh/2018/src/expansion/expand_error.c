/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 02:33:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/28 21:59:04 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"
#include "expansion.h"
#include "expansion_errors.h"

int				expand_error(int error, t_ret *ret, t_exp *par, t_s_env *e)
{
	static t_error	err[] = {
		ERR_NONE_FUNC, ERR_SYNTAX_FUNC, ERR_MODIFIER_FUNC, ERR_UNHANDLED_FUNC,
		ERR_MALLOC_FUNC, ERR_DIRECTORY_STACK_FUNC, ERR_GIVEN_FUNC,
		ERR_NO_SUCH_USER_FUNC, ERR_AMBIGUOUS_FUNC, ERR_PIPE_FUNC,
		ERR_FCNTL_FUNC, ERR_FORK_FUNC, ERR_NO_MATCH_FUNC,
	};

	if (error > 0 && error < (int)(sizeof(err) / sizeof(err[0])))
	{
		ft_dprintf(STDERR_FILENO, "%s: ", e->progname);
		if (e->filein)
			ft_dprintf(STDERR_FILENO, "line %ld: ", e->filein);
		err[error].handler(ret, par);
	}
	e->err_exp = 1;
	expand_free_t_ret(ret, 0);
	free_quote(&par->quote);
	return (1);
}
