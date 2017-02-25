/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 02:07:44 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/25 00:25:54 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		ft_free_parse(t_parse **new)
{
	t_parse		*tmp;

	if (new && *new)
	{
		tmp = *new;
		while (tmp->prev)
		{
			tmp = tmp->prev;
			ft_memset(tmp->next, 0, sizeof(*tmp));
			free(tmp->next);
		}
		if (tmp->cmd)
			free(tmp->cmd);
		ft_memset(tmp, 0, sizeof(*tmp));
		free(tmp);
		tmp = NULL;
	}
}

static void		*parse_error(char *s1, char *s2, t_parse *new)
{
	ft_putstr_fd(s1, 2);
	ft_putendl_fd(s2, 2);
	ft_free_parse(&new);
	return (NULL);
}

static t_parse	*parse_new(char *cmd, t_parse *prev)
{
	t_parse		*new;

	if ((new = (t_parse *)malloc(sizeof(*new))) == NULL)
		return (parse_error("21sh: Memory insufficient.", NULL, prev));
	ft_memset(new, 0, sizeof(*new));
	if (prev)
		prev->next = new;
	new->prev = prev;
	new->cmd = cmd;
	new->next = NULL;
	return (new);
}

static t_parse	*semicolon_check(t_env *e)
{
	t_parse		*new;
	char		*cmd;
	char		*tmp;

	new = NULL;
	if ((cmd = ft_strdup(e->hist->cmd)) == NULL)
		return (parse_error("21sh: Can't duplicate :", e->hist->cmd, new));
	while (cmd && *cmd)
	{
		if ((tmp = ft_strchr(cmd, ';')) != NULL)
			*tmp = '\0';
		if (new && *cmd == '\0')
			return (parse_error("21sh: parse error near ", "`;;'", new));
		if ((new = parse_new(cmd, new)) == NULL)
			break ;
		cmd = (tmp) ? tmp + 1 : NULL;
	}
	while (new && new->prev)
		new = new->prev;
	return (new);
}

void			parse_command(t_env *e)
{
	t_parse		*parse;
	char		**args;

	parse = semicolon_check(e);
	while (parse)
	{
		if ((args = split_command(parse->cmd, e)) != NULL)
		{
			pipes_check(args, e);
			ft_free(&args);
		}
		else
			ft_putendl_fd("21sh: Parsing failed.", 2);
		if (parse->next == NULL)
			break ;
		parse = parse->next;
	}
	hist_add(e, parse);
	ft_free_parse(&parse);
}
