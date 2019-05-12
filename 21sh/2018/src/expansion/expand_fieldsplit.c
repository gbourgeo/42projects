/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_fieldsplit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/05 15:31:37 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/29 02:21:02 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell_lib.h"
#include "shell_env.h"
#include "expansion.h"
#include "expansion_errors.h"

static char		check_quote(char c, char quote)
{
	if (quote == c)
		return (0);
	if (quote == 0)
		return (c);
	return (quote);
}

static char		*check_word(char *str, const char *ifs, t_ret **ret)
{
	char		quote;

	quote = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '"')
			quote = check_quote(*str, quote);
		else if (*str == '\\' && quote != '\'')
		{
			if (param_addchar(*str++, *ret) || param_addchar(*str++, *ret))
				return (NULL);
			continue ;
		}
		if (quote == 0 && ft_strchr(ifs, *str))
			return (str);
		if (param_addchar(*str, *ret))
			return (NULL);
		str++;
	}
	return (str);
}

static int		get_word(char *str, const char *ifs, t_ret **ret)
{
	while (*str)
	{
		while (ft_strchr(ifs, *str))
			str++;
		if (!*str || !(str = check_word(str, ifs, ret)) || !*str)
			break ;
		if (!((*ret)->next = ft_memalloc(sizeof(**ret))))
			return (ERR_MALLOC);
		*ret = (*ret)->next;
	}
	return ((str) ? ERR_NONE : ERR_MALLOC);
}

static char		*remove_ifs_characters_at_start_and_end(char *word, t_s_env *e)
{
	char		*ifs;
	char		*w;

	if (!(ifs = sh_getnenv("IFS", e->public_env)))
		ifs = sh_getnenv("IFS", e->private_env);
	w = word;
	if (!ifs || !ft_strcmp(ifs, IFS_DEFAULT))
	{
		while (ft_strchr(IFS_DEFAULT, *w))
			w = ft_strcpy(w, w + 1);
		if ((w = word + ft_strlen(word)) != word)
			w--;
		while (ft_strchr(IFS_DEFAULT, *w) && w != word && *(w - 1) != '\\')
			*w-- = '\0';
		return (ifs);
	}
	while (ft_strchr(IFS_DEFAULT, *w) && ft_strchr(ifs, *w))
		w = ft_strcpy(w, w + 1);
	if ((w = word + ft_strlen(word)) != word)
		w--;
	while (ft_strchr(IFS_DEFAULT, *w) && ft_strchr(ifs, *w)
	&& w != word && *(w - 1) != '\\')
		*w-- = '\0';
	return (ifs);
}

int				expand_fieldsplit(t_ret **ret, t_s_env *e)
{
	char		*ifs;
	char		*ptr;
	int			error;

	error = ERR_NONE;
	if ((*ret)->word && *(*ret)->word
	&& (ifs = remove_ifs_characters_at_start_and_end((*ret)->word, e)))
	{
		ptr = (*ret)->word;
		ft_memset(*ret, 0, sizeof(char *) + sizeof(size_t) + sizeof(size_t));
		error = get_word(ptr, ifs, ret);
		free(ptr);
	}
	return (error);
}
