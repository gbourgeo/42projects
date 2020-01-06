/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 21:17:34 by mmonier           #+#    #+#             */
/*   Updated: 2019/10/03 18:35:12 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"
#include "asm.h"

void				print_usage(char *err)
{
	ft_dprintf(2, "asm : illegal option -- %s\n", err);
	ft_dprintf(2, "usage: ./asm [-Pdfnops] [file, ...]\n");
	ft_dprintf(2, "-h, --help to see options\n");
	exit(1);
}

static int			set_msk(t_env *e, char c)
{
	static t_flags	tab[8] = {DASH_N, DASH_O, DASH_P, DASH_GP,
		DASH_D, DASH_S, DASH_F};
	size_t			i;

	i = 0;
	if (c == 'h')
		asm_helper();
	while (i < sizeof(tab) / sizeof(tab[i]))
	{
		if (c == tab[i].opt)
		{
			e->flag |= tab[i].msk;
			e->flag |= ATLST_ONE;
			return (1);
		}
		i++;
	}
	return (0);
}

static void			check_err(char *str)
{
	int i;
	int len;

	i = 1;
	len = ft_strlen(str);
	if (ft_strcmp(str, "--help") == 0)
		asm_helper();
	else if (str[0] == '-' && str[1] == '-' && len != 2)
		print_usage("-");
	else if (str[0] == '-')
	{
		while (str[i])
		{
			if (str[i] == '-' && i != 1)
				print_usage(&str[i - 1]);
			i++;
		}
	}
}

int					parse_flag(t_env *e, char **av, int i)
{
	int j;

	while (av[i])
	{
		j = 0;
		if (!av[i][j])
			return (i);
		check_err(av[i]);
		while (av[i][j])
		{
			if (av[i][j] == '-' && av[i][j + 1] == '-')
				return (i + 1);
			if (j == 0 && av[i][j] != '-')
				return (i);
			if (j != 0 && av[i][j] == '-')
				return (i);
			if (av[i][j] != '-')
				if (set_msk(e, av[i][j]) == 0)
					print_usage(&av[i][j]);
			j++;
		}
		i++;
	}
	return (i);
}
