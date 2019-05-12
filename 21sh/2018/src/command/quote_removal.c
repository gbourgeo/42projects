/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 00:07:12 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/28 16:22:29 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion.h"
#include "quote_removal.h"
#include "command.h"

static void		remove_quote(char *str, char *quote, size_t *i)
{
	if (!*quote)
	{
		*quote = str[*i];
		ft_strcpy(str + *i, str + *i + 1);
		(*i)--;
	}
	else if (*quote == str[*i])
	{
		*quote = 0;
		ft_strcpy(str + *i, str + *i + 1);
		(*i)--;
	}
}

static void		remove_back(char *str, char *quote, size_t *i)
{
	if (*quote == '\'')
		return ;
	else if (*quote == '"'
	&& (str[*i + 1] == '$' || str[*i + 1] == '`' || str[*i + 1] == '"'
		|| str[*i + 1] == '\\' || str[*i + 1] == '\n'))
		ft_strcpy(str + *i, str + *i + 1);
	else if (!*quote)
		ft_strcpy(str + *i, str + *i + 1);
}

void			check_str(char *str)
{
	static t_q_removal	removal[] = {
		{ '\'', remove_quote }, { '"', remove_quote }, { '\\', remove_back },
	};
	size_t				i;
	size_t				j;
	char				quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		j = 0;
		while (j < sizeof(removal) / sizeof(removal[0]))
		{
			if (removal[j].value == str[i])
			{
				removal[j].handler(str, &quote, &i);
				break ;
			}
			j++;
		}
		i++;
	}
}

void			quote_removal(t_argument *arg)
{
	size_t		i;

	if (arg)
		while (arg)
		{
			i = 0;
			if (arg->cmd)
				while (arg->cmd[i])
					check_str(arg->cmd[i++]);
			arg = arg->next;
		}
}
