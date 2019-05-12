/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_options.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 16:25:18 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/03 19:14:27 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin_env.h"

static int		env_options_loop(char **cmd, t_e_opt *opt)
{
	static t_opt	options[] = {
		ENV_OPTION_LESS, ENV_OPTION_I, ENV_OPTION_V, ENV_OPTION_P, ENV_OPTION_U,
	};
	size_t			nb;

	nb = 0;
	while (nb < sizeof(options) / sizeof(options[0]))
	{
		if (cmd[opt->i][opt->j] == options[nb].value)
			return (options[nb].handler(cmd, opt));
		nb++;
	}
	return (ERR_ILLEGAL_OPT);
}

int				env_options(char **cmd, t_e_opt *opt)
{
	int			error;

	opt->i = 1;
	while (cmd[opt->i] && cmd[opt->i][0] == '-'
		&& !(opt->options & BUILTIN_OPT_END))
	{
		if (!cmd[opt->i][1])
			opt->options |= BUILTIN_OPT_I;
		else
		{
			opt->j = 0;
			while (cmd[opt->i] && cmd[opt->i][++(opt->j)])
			{
				if ((error = env_options_loop(cmd, opt)) != ERR_OK)
					return (error);
				if (opt->options & BUILTIN_OPT_P
				|| opt->options & BUILTIN_OPT_U)
					break ;
			}
			opt->j = 0;
		}
		++(opt->i);
	}
	return (ERR_OK);
}
