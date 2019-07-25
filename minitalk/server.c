/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/07 21:27:44 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/02/09 21:21:00 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void		signal_handler(int status);
static char		convert_bin_to_dec(int *ret);
static int		power_of_two(int pow);

int				main(void)
{
	pid_t		pid;

	pid = getpid();
	ft_putendl("Welcome to Project Minitalk\n");
	ft_putstr("Share this PID to your client: ");
	ft_putnbr(pid);
	ft_putendl("\nThe chat will begin from here. Have fun!\n");
	while (1)
	{
		signal(SIGUSR1, signal_handler);
		signal(SIGUSR2, signal_handler);
		pause();
	}
	return (0);
}

static void		signal_handler(int status)
{
	static int	ret[8];
	static int	i = 0;
	static int	j = 0;
	static char	*text = NULL;

	if (text == NULL)
		text = (char*)malloc(sizeof(char) * TEXT_SIZE);
	if (status == SIGUSR1)
		ret[i++] = 1;
	if (status == SIGUSR2)
		ret[i++] = 0;
	if (i > 7)
	{
		if (j == TEXT_SIZE)
			text = ft_realloc(text, TEXT_SIZE);
		text[j++] = convert_bin_to_dec(ret);
		if (text[j - 1] == 0)
		{
			ft_putendl(text);
			j = 0;
		}
		i = 0;
	}
}

static char		convert_bin_to_dec(int *ret)
{
	int			i;
	int			c;

	i = 7;
	c = 0;
	while (i >= 0)
	{
		if (ret[i] == 1)
			c += power_of_two(i);
		i--;
	}
	return ((char)c);
}

static int		power_of_two(int pow)
{
	int			res;

	res = 1;
	while (pow > 0)
	{
		res = res * 2;
		pow--;
	}
	return (res);
}
