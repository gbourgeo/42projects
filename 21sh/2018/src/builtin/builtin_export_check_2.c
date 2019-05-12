/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_check_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 18:28:31 by tsisadag          #+#    #+#             */
/*   Updated: 2019/04/29 13:49:41 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "builtin_export.h"

int		valid_id(char *arg)
{
	if ((!ft_isalpha(arg[0]) && arg[0] != '_')
	|| (!has_invalid_id(arg)))
	{
		ft_dprintf(2, "42sh: export: `%s': not a valid identifier\n",
				arg);
		return (0);
	}
	return (1);
}

int		has_invalid_id(char *arg)
{
	int i;

	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '=' && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int		illegal_option_export(char *option)
{
	int i;

	i = 1;
	while (option[i])
	{
		if (option[i] != 'p')
		{
			ft_dprintf(2, "42sh: export: -%c: invalid option\nexport: usage: "
					"export [-p] name [name ...]\n", option[i]);
			return (2);
		}
		i++;
	}
	return (0);
}

int		count_strarr(char **str_array)
{
	int i;

	i = 0;
	if (str_array)
		while (str_array[i])
			i++;
	return (i);
}
