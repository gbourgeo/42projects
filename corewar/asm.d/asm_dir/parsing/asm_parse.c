/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 01:48:11 by dbaffier          #+#    #+#             */
/*   Updated: 2019/10/25 22:47:43 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include "asm.h"

static int	str_alnum(char *str)
{
	int		val;
	int		i;

	i = 0;
	val = 0;
	while (str[i])
	{
		if (ft_isalnum(str[i]))
			val++;
		i++;
	}
	return (val > 0 ? 1 : 0);
}

static int	assign_next(t_env *e, char **line, t_aolist *head)
{
	static int	c = 0;
	t_aolist	*new;

	if (c == 0 && ++c)
	{
		head->line = e->line;
		if ((tok_create(e, head, line)) > 0)
			return (ERR_MALLOC);
	}
	else if (str_alnum(*line))
	{
		if (!(new = ft_memalloc(sizeof(t_aolist))))
			return (ERR_MALLOC);
		new->line = e->line;
		if ((tok_create(e, new, line)) > 0)
			return (ERR_MALLOC);
		push_front(e->aolist, new, 0);
	}
	return (0);
}

static int	token_lst(t_env *e)
{
	int			ret;
	t_aolist	*lst;
	char		*line;

	line = NULL;
	if (!(lst = ft_memalloc(sizeof(t_aolist))))
		return (ERR_MALLOC);
	e->aolist = lst;
	while ((ret = get_next_line(e->fd, &line)) > 0)
	{
		e->line = e->line + 1;
		if (line && line[0] != '\0' && line[0] != '#')
			assign_next(e, &line, lst);
		free(line);
	}
	return (0);
}

int			parser(t_env *e, char *file)
{
	int		ret;

	if ((ret = asm_file_open(e, file)) > 0)
		return (ret);
	if ((ret = token_lst(e)) > 0)
		return (ERR_MALLOC);
	if ((ret = syntax_analysis(e, e->aolist)) > 0)
		return (ERR_MALLOC);
	return (0);
}
