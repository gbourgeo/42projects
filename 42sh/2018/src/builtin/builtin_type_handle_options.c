/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_type_handle_options.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsisadag <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 17:13:24 by tsisadag          #+#    #+#             */
/*   Updated: 2019/03/09 18:37:45 by tsisadag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "builtin_type.h"

t_type	*def_s_type(t_execute *exec)
{
	t_type	*type;

	type = ft_memalloc(sizeof(t_type));
	type->opt = 0;
	type->opt_p = 0;
	type->opt_f = 0;
	type->opt_bigp = 0;
	type->opt_a = 0;
	type->opt_t = 0;
	type->cnt_opt = count_options(exec->cmd);
	return (type);
}

int		count_options(char **av)
{
	int i;
	int count;

	i = 1;
	count = 0;
	while (av[i])
	{
		if (av[i][0] == '-' && av[i][1])
			count++;
		else
			return (count);
		i++;
	}
	return (count);
}

int		illegal_option(char *option)
{
	int i;

	i = 1;
	while (option[i])
	{
		if (option[i] != 'a' && option[i] != 'f' && option[i] != 'p'
				&& option[i] != 't' && option[i] != 'P')
		{
			ft_dprintf(2, "42sh: type: -%c: invalid option\ntype: usage: "
					"type [-afptP] name [name ...]\n", option[i]);
			return (2);
		}
		i++;
	}
	return (0);
}

void	get_option(char *option, t_type *type, int i)
{
	while (option[i])
	{
		option[i] == 'a' ? type->opt_a = 1 : type->opt_a;
		option[i] == 'f' ? type->opt_f = 1 : type->opt_f;
		if (option[i] == 'p')
		{
			type->opt_t = 0;
			type->opt_p = 1;
		}
		if (option[i] == 't')
		{
			type->opt_bigp = 0;
			type->opt_p = 0;
			type->opt_t = 1;
		}
		if (option[i] == 'P')
		{
			type->opt_t = 0;
			type->opt_bigp = 1;
		}
		i++;
	}
	if (type->opt_a || type->opt_f || type->opt_p ||
		type->opt_t || type->opt_bigp)
		type->opt = 1;
}
