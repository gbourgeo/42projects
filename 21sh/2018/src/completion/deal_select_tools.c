/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_select_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 03:37:52 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/23 13:04:03 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "put.h"
#include "shell_lib.h"
#include "struct.h"
#include "libft.h"

void		put_branch(t_slct *select, t_cpl_e env, t_line *line, int *car_ret)
{
	if (select && env.len > env.lvl + 1)
	{
		env.bru[env.lvl] = select->mln->value;
		env.lvl += 1;
		put_branch(select->down, env, line, car_ret);
		env.lvl -= 1;
	}
	else if (select)
	{
		env.bru[env.lvl] = select->mln->value;
		env.bru[env.lvl + 1] = '\0';
		env.lvl += 1;
		ft_put_tree(select->mln->tern_next, env, line, car_ret);
		env.lvl -= 1;
	}
	if (select && select->next)
		put_branch(select->next, env, line, car_ret);
}

void		put_select_branch(t_slct *select, t_cpl_e env, t_line *line)
{
	int		car_ret;

	car_ret = 0;
	env.lvl = 0;
	put_branch(select, env, line, &car_ret);
}

void		put_tree_branch(t_tree *tree, t_cpl_e env, t_line *line)
{
	int		car_ret;

	car_ret = 0;
	env.lvl = 0;
	ft_put_tree(tree, env, line, &car_ret);
}

int			have_to_expand(t_line *line)
{
	char	*space;
	char	*slash;
	char	*dol;

	space = sh_strrchr(line->curr->buff, ' ');
	slash = sh_strrchr(line->curr->buff, '/');
	if (!(dol = sh_strrchr(line->curr->buff, '$')) || (!ft_isalnum(*(dol + 1))
				&& *(dol + 1) != '{' && *(dol + 1) && *(dol + 1) != '_'))
		return (0);
	if (!space && dol)
		return (1);
	if (space && !slash && dol > space)
		return (1);
	if (space && slash && dol > slash && dol > space)
		return (1);
	return (0);
}
