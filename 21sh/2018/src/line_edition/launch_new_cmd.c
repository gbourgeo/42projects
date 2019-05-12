/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_new_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 20:31:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/16 20:06:42 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "token.h"
#include "command.h"

static char		get_quote(char *c, char quote)
{
	if (quote == 0)
	{
		if (*c == '$' && (*(c + 1) == '(' || (*c + 1) == '{'))
			return ('$');
		if (*c == '\n')
			return (0);
		return (*c);
	}
	if ((*c == ')' || *c == '}') && quote == '$')
		return (0);
	if (*c == '\n' && quote == '#')
		return (0);
	if (quote == *c)
		return (0);
	return (quote);
}

static void		remove_line_continuation(char **line)
{
	size_t		i;
	char		quote;

	i = 0;
	quote = 0;
	if (line && *line)
		while ((*line)[i])
		{
			if (ft_strchr("'#`$(){}\n", (*line)[i]))
				quote = get_quote(&(*line)[i], quote);
			if (!quote && (*line)[i] == '\\' && (*line)[i + 1] == '\n')
				ft_strcpy(&(*line)[i], &(*line)[i + 2]);
			else
				i++;
		}
}

void			launch_new_cmd(char **line, t_s_env *e)
{
	t_token		*tokens;
	t_m_list	*tree;

	tokens = NULLTOKEN;
	tree = NULLLIST;
	remove_line_continuation(line);
	if ((tokens = tokenise(line, e)) != NULLTOKEN)
	{
		if (!e->forked && !e->interactive)
			term_restore(&e->save);
		if ((tree = parse(line, &tokens, e)) != NULLLIST)
			execute_list(tree, e);
		if (!e->forked && !e->interactive)
			define_new_term(&e->save);
		free_m_list(&tree);
		free_token(&tokens);
	}
}
