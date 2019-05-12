/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_comp_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 17:00:18 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/28 19:18:57 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "put.h"
#include "libft.h"
#include "shell_term.h"
#include "shell.h"
#include "shell_lib.h"

int			check_is_file(char *buff, t_line *line)
{
	int		i;

	i = line->len - 1;
	while (i >= 0 && !ft_strchr("&;| /", buff[i]))
		i--;
	while (i >= 0 && (buff[i] == ' ' || buff[i] == '\t' || buff[i] == '\\'))
		i--;
	if ((i == -1 || ft_strchr(";&|", buff[i])) && !ft_strchr("./", buff[0]))
		return (0);
	return (1);
}

static int	erase_complet(char *ptr, t_line *line)
{
	ft_bzero(ptr, ft_strlen(ptr));
	tputs(tgetstr("do", NULL), 1, ft_pchar);
	tputs(tgetstr("cr", NULL), 1, ft_pchar);
	tputs(tgetstr("cd", NULL), 1, ft_pchar);
	tputs(tgetstr("up", NULL), 1, ft_pchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, (line->lprompt + line->index)
				% line->nb_col), 1, ft_pchar);
	return (line->len);
}

static void	finish_glob(t_line *line, t_slst **tmp, int nb_line)
{
	t_slst	*to_free;

	while ((to_free = *tmp))
	{
		*tmp = (*tmp)->next;
		free(to_free->str);
		free(to_free);
	}
	while (nb_line--)
		tputs(tgetstr("up", NULL), 1, ft_pchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, line->lprompt), 1, ft_pchar);
}

static void	get_new_glob(t_line *line, t_slst *tmp, int pos)
{
	int		i;
	t_slst	*to_free;
	int		tmp_len;
	int		len;

	tmp_len = erase_complet(&line->curr->buff[pos], line);
	line->len = (size_t)pos;
	while ((to_free = tmp))
	{
		if (line->len / MAX_SHELL_LEN < line->len
				+ (len = ft_strlen(tmp->str)) / MAX_SHELL_LEN)
			get_buff_realloc(line, len);
		i = -1;
		while (tmp->str[++i])
			line->curr->buff[line->len++] = tmp->str[i];
		line->curr->buff[line->len++] = ' ';
		tmp = tmp->next;
		free(to_free->str);
		free(to_free);
	}
	finish_glob(line, &tmp, (tmp_len / line->nb_col));
}

void		set_new_glob(t_line *line, t_slst *tmp, int pos)
{
	if (tmp)
	{
		while (tmp->prev)
			tmp = tmp->prev;
		get_new_glob(line, tmp, pos);
		tputs(tgetstr("cd", NULL), 1, ft_pchar);
		ft_putstr(line->curr->buff);
		line->len = ft_strlen(line->curr->buff);
		line->index = line->len;
	}
}
