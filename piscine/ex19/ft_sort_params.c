/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 12:56:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/07/13 13:08:42 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

static int	ft_strcmp(char *a, char *b)
{
	int		i;

	i = 0;
	while (a[i] && b[i] && a[i] == b[i])
		i++;
	return (a[i] - b[i]);
}

static void	ft_sort_params(char **argv)
{
	int		i;
	int		ret;
	char	*swap;

	i = 1;
	while (argv[i + 1])
	{
		ret = ft_strcmp(argv[i], argv[i + 1]);
		if (ret > 0)
		{
			swap = argv[i];
			argv[i] = argv[i + 1];
			argv[i + 1] = swap;
			if (i > 0)
				i--;
		}
		else
			i++;
	}
}

static int	ft_strlen(char *a)
{
	int		i;

	i = 0;
	while (a[i])
		i++;
	return (i);
}

static void	ft_print_params(char **av)
{
	int		i;

	i = 1;
	while (av[i])
	{
		write(1, av[i], ft_strlen(av[i]));
		write(1, "\n", 1);
		i++;
	}
}

int			main(int ac, char **av)
{
	if (ac == 1)
		return (0);
	ft_sort_params(av);
	ft_print_params(av);
	return (0);
}
