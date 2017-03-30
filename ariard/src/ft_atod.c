/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 22:12:55 by root              #+#    #+#             */
/*   Updated: 2017/03/28 22:14:03 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static double	ft_plus(char *str)
{
	int			i;
	double		res;

	i = 0;
	res = 0.0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		i++;
	while (i-- > 0)
	{
		res = res + str[i] - '0';
		res = res / 10.0;
	}
	return (res);
}

double			ft_atod(char *str)
{
	int			i;
	double		res;
	char		isneg;

	i = 0;
	res = 0.0;
	isneg = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
	{
		isneg = 1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10.0;
		res = res + str[i++] - '0';
	}
	if (str[i] == '.')
		res += ft_plus(&str[i + 1]);
	return ((isneg ? -res : res));
}
