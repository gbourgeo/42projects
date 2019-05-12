/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tilde_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 18:56:52 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/21 19:52:32 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pwd.h>
#include "libft.h"
#include "shell_lib.h"
#include "expansion_tilde.h"
#include "expansion_errors.h"

int				expand_tilde_env(t_ret *ret, t_ret *parame, t_exp *param)
{
	if (parame->substitute)
		return (expand_tilde_not(ret, parame->word));
	return (param_addstr(sh_getnenv("HOME", param->e->public_env), ret));
}

int				expand_tilde_plus(t_ret *ret, t_ret *parame, t_exp *param)
{
	if (!parame->word[1]
	|| (tilde_digit(parame->word + 1) && !ft_atoi(parame->word + 1)))
		return (param_addstr(sh_getnenv("PWD", param->e->public_env), ret));
	return (expand_tilde_not(ret, parame->word));
}

int				expand_tilde_minus(t_ret *ret, t_ret *parame, t_exp *param)
{
	if (!parame->word[1]
	|| (tilde_digit(parame->word + 1) && !ft_atoi(parame->word + 1)))
		return (param_addstr(sh_getnenv("OLDPWD", param->e->public_env), ret));
	return (expand_tilde_user(ret, parame, param));
}

int				expand_tilde_user(t_ret *ret, t_ret *parame, t_exp *param)
{
	struct passwd	*user;

	(void)param;
	if ((user = getpwnam(parame->word)) == NULL)
	{
		if (param_addstr(parame->word, ret))
			return (ERR_MALLOC);
		return (ERR_NO_SUCH_USER);
	}
	if (param_addstr(user->pw_dir, ret))
		return (ERR_MALLOC);
	return (ERR_NONE);
}
