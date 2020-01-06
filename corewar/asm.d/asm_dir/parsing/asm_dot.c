/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_dot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 00:02:04 by dbaffier          #+#    #+#             */
/*   Updated: 2019/11/02 21:23:43 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include "ft_printf.h"

static char			*dup_dot(char *line, size_t *i)
{
	char		*new;
	size_t		s;
	size_t		e;

	s = *i;
	e = 0;
	while (line[*i] && line[*i] != '\"' && line[*i] != '\t' && line[*i] != ' ')
		*i = *i + 1;
	if (!(new = malloc(sizeof(char) * (*i - s) + 1)))
		return (NULL);
	while (line[s] && s < *i)
	{
		new[e] = line[s];
		s++;
		e++;
	}
	new[e] = '\0';
	return (new);
}

static char			*dup_all(char *val, size_t *i)
{
	char		*new;
	size_t		s;
	size_t		e;

	s = *i;
	e = 0;
	while (val[*i] && val[*i] != '\"')
		*i = *i + 1;
	*i = *i + 1;
	if (!(new = malloc(sizeof(char) * (*i - s) + 1)))
		return (NULL);
	while (val[s] && s < (*i - 1))
	{
		new[e] = val[s];
		s++;
		e++;
	}
	new[e] = '\0';
	return (new);
}

static int			quoted(char *val, size_t *i)
{
	int		j;

	while (val[*i] && (val[*i] == ' ' || val[*i] == '\t'))
		*i = *i + 1;
	if (val[*i] == '\"')
	{
		*i = *i + 1;
		j = *i;
		while (val[j])
		{
			if (val[j] == '\"')
			{
				j++;
				while (val[j] && (val[j] == ' ' || val[j] == '\t'))
					j++;
				if (val[j] == '\0')
					return (1);
				else
					return (0);
			}
			j++;
		}
	}
	return (0);
}

static char			*dup_multiple(t_env *e, char *val, size_t *i)
{
	char	*dup;
	char	*line;

	line = NULL;
	if ((dup = ft_strjoin(&val[*i], "\n")) == NULL)
		return (NULL);
	while (val[*i])
		*i = *i + 1;
	while (get_next_line(e->fd, &line) > 0)
	{
		e->line = e->line + 1;
		dup = ft_strjoinfree(dup, line, 1);
		dup = ft_strjoinfree(dup, "\n", 1);
		if (line && ft_strchr(line, '"'))
			break ;
		free(line);
	}
	free(line);
	if (ft_strchr(dup, '"') && dup[ft_strlen(dup) - 2] == '"')
	{
		dup[ft_strlen(dup) - 2] = '\0';
		return (dup);
	}
	free(dup);
	return (NULL);
}

int					create_dot(t_env *e, t_token **head, char *val, size_t *i)
{
	t_token		*ptr;
	t_token		*new;
	t_token		*next;

	if (!(new = ft_memalloc(sizeof(t_token))))
		return (ERR_MALLOC);
	new->lab = dup_dot(val, i);
	new->type |= DOT;
	if (!(next = ft_memalloc(sizeof(t_token))))
		return (ERR_MALLOC);
	next->lab = quoted(val, i) ? dup_all(val, i) : dup_multiple(e, val, i);
	next->type |= DOT_ARG;
	new->next = next;
	if (*head == NULL)
		*head = new;
	else
	{
		ptr = *head;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
	return (0);
}
