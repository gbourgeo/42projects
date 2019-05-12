/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_parameter_value.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 04:42:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/10 20:39:29 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell_lib.h"
#include "expansion_is.h"
#include "expansion_dollar.h"
#include "expansion_errors.h"
#include "expansion_special.h"

static int		expand_argc(t_ret *subs, t_ret *para, t_exp *param)
{
	char		*nbr;
	int			error;

	nbr = ft_itoa(param->e->ac - 1);
	error = param_addstr(nbr, subs);
	if (nbr)
		free(nbr);
	if (error)
		return (special_error(error, subs->word));
	para->hash = 0;
	para->freeable = 1;
	para->substitute = subs->word;
	return (ERR_NONE);
}

static int		expand_argv(t_ret *subs, t_ret *para, t_exp *param)
{
	char		*word;
	int			nb;

	word = &para->word[para->brace + para->hash + 1];
	if (para->brace)
		while (*word)
			if (!ft_isdigit(*word++))
				return (ERR_SYNTAX);
	word = &para->word[para->brace + para->hash + 1];
	nb = ft_atoi(word);
	subs->word = (nb < param->e->ac) ? param->e->av[nb] : NULL;
	para->substitute = subs->word;
	para->freeable = 0;
	return (ERR_NONE);
}

static int		expand_env(t_ret *subs, t_ret *para, t_exp *param)
{
	char		*word;

	word = &para->word[para->brace + para->hash + 1];
	if (para->brace)
		while (*word)
			if (!is_valid_name(*word++))
				return (ERR_SYNTAX);
	word = &para->word[para->brace + para->hash + 1];
	if (!(subs->word = sh_getnenv(word, param->e->public_env)))
		subs->word = sh_getnenv(word, param->e->private_env);
	para->substitute = subs->word;
	para->freeable = 0;
	return (ERR_NONE);
}

int				expand_dollar_parameter_value(t_ret *parameter, t_exp *param)
{
	static t_dollar	dollar[] = {
		{ is_special, expand_dollar_special },
		{ ft_isdigit, expand_argv }, { is_valid_name, expand_env },
	};
	size_t			i;
	t_ret			substitute;
	char			*word;

	i = 0;
	ft_memset(&substitute, 0, sizeof(substitute));
	word = &parameter->word[parameter->brace + parameter->hash + 1];
	if (!*word && !parameter->hash)
		return (ERR_SYNTAX);
	if (is_expand_null(parameter))
		return (expand_argc(&substitute, parameter, param));
	while (i < sizeof(dollar) / sizeof(dollar[0]))
	{
		if (dollar[i].check(word[0]))
			return (dollar[i].handler(&substitute, parameter, param));
		i++;
	}
	return (special_error(ERR_SYNTAX, substitute.word));
}
