/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 18:00:21 by dbaffier          #+#    #+#             */
/*   Updated: 2019/11/12 14:42:36 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "asm.h"

static int		create_token(t_token **head, char *line, size_t *i)
{
	if (grep_opcode(head, line, i) > 0)
		return (ERR_MALLOC);
	return (0);
}

static int		tokenize(t_env *e, t_token **head, char **line, size_t *i)
{
	char	*s;

	s = *line;
	if (s[*i] == '.')
		return (create_dot(e, head, *line, i));
	if (ft_strchr(&s[*i], COMMENT_CHAR))
	{
		if (asm_comment(e->save, line, COMMENT_CHAR) > 0)
			return (ERR_MALLOC);
	}
	else if (ft_strchr(*line, ';'))
	{
		if (asm_comment(e->save, line, ';') > 0)
			return (ERR_MALLOC);
	}
	s = *line;
	if (!s[*i])
		return (0);
	if (is_label(*line, *i))
		return (create_label(head, *line, i));
	return (create_token(head, *line, i));
}

static int		loop_tok(t_env *e, t_token **tok, size_t *i, char **dup)
{
	char	*s;

	s = *dup;
	while (s[*i])
	{
		if (s[*i] == ' ' || s[*i] == '\t')
			*i = *i + 1;
		else if (s[*i])
		{
			if (tokenize(e, tok, dup, i) > 0)
				return (ERR_MALLOC);
		}
		if (!*dup)
			return (0);
		s = *dup;
	}
	return (0);
}

int				tok_create(t_env *e, t_aolist *head, char **line)
{
	t_token		*tok;
	size_t		i;

	i = 0;
	tok = NULL;
	e->save = head;
	if (loop_tok(e, &tok, &i, line) == ERR_MALLOC)
		return (ERR_MALLOC);
	head->id = set_id(tok);
	head->size = chunk_size(tok, head->id);
	head->tok = tok;
	e->save = NULL;
	return (0);
}
