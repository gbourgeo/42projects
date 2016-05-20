/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 03:32:53 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/20 02:33:07 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void			ft_stab_value(unsigned int i, int base)
{
	char			res[base];
	int				j;

	j = base;
	while (j-- > 0)
	{
		res[j] = (i % 16) + '0';
		i /= 10;
	}
	write(1, res, base);
	ft_putchar(' ');
}

static void			ft_stab(t_el *el)
{
	unsigned int	i;
	unsigned int	j;
	static t_stab	p[] = { STAB };

	ft_stab_value(el->n_sect & 0xff, 2);
	ft_stab_value(el->n_desc & 0xffff, 4);
	i = 0;
	while (p[i].name)
	{
		if (p[i].n_type == el->n_type)
			break ;
		i++;
	}
	j = ft_strlen(p[i].name);
	while (j++ < 5)
		ft_putchar(' ');
	ft_putstr(p[i].name);
	ft_putchar(' ');
}

static void			ft_value(int len, t_el *elem, t_base *env)
{
	int				i;
	int				j;
	char			res[len];
	char			*base;

	if (elem->type == 'U')
		write(1, "                 ", len);
	else
	{
		base = "0123456789abcdef";
		i = len - 1;
		res[i] = ' ';
		while (i-- > 0)
		{
			j = elem->n_value % 16;
			res[i] = base[j];
			elem->n_value /= 16;
		}
		write(1, res, len);
	}
	ft_putchar(elem->type);
	ft_putchar(' ');
	if (env->options[opt_a] && elem->type == '-')
		ft_stab(elem);
}

static void			ft_do(t_el *elem, t_base *env)
{
	if (env->options[opt_o] || env->options[opt_A])
	{
		ft_putstr(env->file_name);
		if (env->arch_obj_name != NULL)
		{
			ft_putchar(':');
			ft_putstr(env->arch_obj_name);
		}
		ft_putstr(": ");
	}
	if (!env->options[opt_u] && !env->options[opt_j])
		ft_value(env->sect.type, elem, env);
	ft_putstr(elem->name);
	ft_putchar('\n');
}

void				ft_display(t_el *elem, t_base *env)
{
	while (!env->options[opt_p] && env->options[opt_r] && elem->next)
		elem = elem->next;
	while (elem != NULL)
	{
		if (!env->options[opt_none] || env->options[opt_o] ||
			(env->options[opt_g] && elem->type >= 'A' && elem->type <= 'Z') ||
			(env->options[opt_u] && (elem->type == 'u' || elem->type == 'U')) ||
			(env->options[opt_U] && elem->type != 'u' && elem->type != 'U') ||
			env->options[opt_j] || env->options[opt_n] || env->options[opt_p] ||
			env->options[opt_a] || env->options[opt_A] || env->options[opt_r])
		{
			ft_do(elem, env);
		}
		elem = (!env->options[opt_p] && env->options[opt_r]) ?
				elem->prev : elem->next;
	}
}
