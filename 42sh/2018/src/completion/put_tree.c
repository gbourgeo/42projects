/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 01:34:09 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/29 21:54:02 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "put.h"
#include "shell.h"
#include "shell_lib.h"
#include "shell_term.h"

char		*find_start_pos(char *buff)
{
	int		i;

	i = ft_strlen(buff) - 1;
	while (i > 0)
	{
		if (ft_strchr("&|; /${", buff[i]) && buff[i - 1] != '\\')
		{
			if ((buff[i] == '$' && buff[i + 1] != '\'') || buff[i] != '$')
				return (buff + i + 1);
		}
		i--;
	}
	return (buff);
}

static void	get_new_file(t_tree *tern, t_cpl_e env, t_line *line)
{
	char	*chr;
	char	*ptr;
	char	*tmp;

	if (!*((ptr = find_start_pos(line->curr->buff))))
		stercat(line->curr->buff_tmp, env.bru, line->curr->buff);
	else if (!ft_strchr(ptr, '/'))
	{
		if ((chr = ptr) == line->curr->buff)
			chr += 1;
		if ((tmp = sh_strrchr(chr, '$')))
		{
			if (*(tmp + 1) != '\'')
			{
				chr = sh_strrchr(chr, '$') + 1;
				chr = *chr == '{' ? chr + 1 : chr;
			}
		}
		ft_strcpy(chr, env.bru);
	}
	else
		ft_strcpy(sh_strrchr(line->curr->buff, '/') + 1, env.bru);
	ft_strncat(line->curr->buff, (char*)&(tern->value), 1);
}

static void	get_new_buff(t_tree *tern, t_cpl_e env, t_line *line)
{
	char	*ptr;

	if (!tern->tput && *env.put && *(line->e_cmpl) & COMPLETION)
	{
		tputs(tgetstr("me", NULL), 1, ft_pchar);
		tputs(tgetstr("mr", NULL), 1, ft_pchar);
		tern->tput = 1;
		*env.put = 0;
		if (ft_occuc(line->curr->buff, ' '))
			get_new_file(tern, env, line);
		else
		{
			if ((ptr = sh_strrchr(line->curr->buff, '$')))
			{
				ptr = (*(ptr + 1) == '{') ? ptr + 1 : ptr;
				ft_bzero(ptr + 1, ft_strlen(ptr + 1));
				ft_strcpy(ptr + 1, env.bru);
				return ;
			}
			ptr = find_separator(line->curr->buff);
			ft_bzero(ptr, ft_strlen(ptr));
			ft_strcpy(ptr, env.bru);
		}
	}
}

static void	put_space(t_cpl_e env, int *car_ret)
{
	int		nb;

	if (*car_ret < env.nb_col - 1)
	{
		nb = env.lenm - ft_strlen(env.bru) + 1;
		while (nb--)
			write(0, " ", 1);
		// ft_putchars(' ', env.lenm - ft_strlen(env.bru) + 1);
		*car_ret += 1;
	}
	else
	{
		nb = env.lenm - ft_strlen(env.bru) + 1;
		while (nb--)
			write(0, " ", 1);
		// ft_putchars(' ', env.lenm - ft_strlen(env.bru) + 1);
		ft_putchar_fd('\n', 0);
		*car_ret = 0;
		*env.nb_ret += 1;
	}
}

void		ft_put_tree(t_tree *tern, t_cpl_e env, t_line *line, int *car_ret)
{
	if (tern->left)
		ft_put_tree(tern->left, env, line, car_ret);
	if (tern->tern_next && (tern->value != '.' || env.bru[0] == '.'
				|| env.lvl >= 1))
	{
		env.bru[env.lvl] = tern->value;
		env.lvl += 1;
		ft_put_tree(tern->tern_next, env, line, car_ret);
		env.lvl -= 1;
	}
	if (tern && !tern->tern_next)
	{
		env.bru[env.lvl] = '\0';
		deal_type(tern->type, line, env.bru);
		get_new_buff(tern, env, line);
		ft_putstr(env.bru);
		put_space(env, car_ret);
		ft_putstr(RESET);
	}
	if (tern->right)
		ft_put_tree(tern->right, env, line, car_ret);
}
