/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/23 21:23:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2013/12/29 01:40:29 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int		first_test_a(t_lib **l_a, char **ret);
static void		first_test_b(t_lib **l_b, char **ret);

char			*ft_push_swap(t_lib **l_a)
{
	char		*ret;
	t_lib		*l_b;
	int			count;

	ret = NULL;
	l_b = NULL;
	count = 0;
	while (is_l_a_sorted(*l_a) || l_b != NULL)
	{
		count = first_test_a(l_a, &ret);
		first_test_b(&l_b, &ret);
		if (count)
			ps_swap_list(&l_b, l_a, &ret, "pb ");
		if ((is_l_a_sorted(*l_a)) == 0 && l_b != NULL)
			ps_swap_list(l_a, &l_b, &ret, "pa ");

	}
	return (ret);
}

static int		first_test_a(t_lib **l_a, char **ret)
{
	t_lib		*l_c;

	l_c = *l_a;
	ps_goto_end(&l_c);
	if ((*l_a)->nb > l_c->nb && (*l_a)->nb < (*l_a)->next->nb)
	{
		ps_end_to_first(l_a, ret, "rra ");
		first_test_a(l_a, ret);
	}
	if ((*l_a)->nb > l_c->nb)
	{
		ps_first_to_end(l_a, ret, "ra ");
		first_test_a(l_a, ret);
	}
	if ((*l_a)->nb > (*l_a)->next->nb)
		ps_swap(l_a, ret, "sa ");
	return (is_l_a_sorted(*l_a));
}

static void		first_test_b(t_lib **l_b, char **ret)
{
	t_lib		*l_d;

	l_d = *l_b;
	ps_goto_end(&l_d);
	if (*l_b)
	{
		if ((*l_b)->next)
		{
			if (l_d->nb > (*l_b)->nb && (*l_b)->nb > (*l_b)->next->nb)
			{
				ps_end_to_first(l_b, ret, "rrb ");
				first_test_b(l_b, ret);
			}
			if ((*l_b)->nb < l_d->nb)
			{
				ps_first_to_end(l_b, ret, "rb ");
				first_test_b(l_b, ret);
			}
			if ((*l_b)->nb < (*l_b)->next->nb)
				ps_swap(l_b, ret, "sb ");
		}
	}
}
