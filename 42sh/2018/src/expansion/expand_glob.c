/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_glob.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 03:52:43 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/29 13:42:20 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_loop.h"
#include "expansion_errors.h"
#include "struct.h"
#include "shell.h"
#include "libft.h"
#include "put.h"
#include "globing.h"

static int		get_glob_len(t_slst *glob)
{
	int	len;

	len = 0;
	while (glob)
	{
		len += ft_strlen(glob->str) + 1;
		glob = glob->next;
	}
	return (len);
}

static char		*get_glob_str(t_slst *glob)
{
	char	*str;
	int		i;
	int		j;

	if (!(str = ft_memalloc(sizeof(char) * get_glob_len(glob))))
		return (NULL);
	i = 0;
	while (glob)
	{
		j = -1;
		while (glob->str[++j])
			str[i++] = glob->str[j];
		if (glob->next)
			str[i++] = ' ';
		glob = glob->next;
	}
	return (str);
}

static void		free_exp_glob(t_slst *glob)
{
	if (!glob)
		return ;
	free_exp_glob(glob->next);
	free(glob->str);
	free(glob);
}

static t_slst	*get_exp_glob(t_ret *ret, char *ptr, char *tmp)
{
	t_line	*line;
	t_slst	*glob;

	line = get_struct();
	GET_TREE(line->tree, FILES) = create_file_tree(".", NULL, line->tree[1]);
	if (GET_TREE(line->tree, TMP)
		|| (GET_TREE(line->tree, TMP) = set_tmp(ptr, 1)))
		glob = deal_globing(ptr, GET_TREE(line->tree, TMP));
	else
		glob = deal_globing(ptr, GET_TREE(line->tree, FILES));
	if (!glob)
		param_addstr(tmp, ret);
	while (glob && glob->prev)
		glob = glob->prev;
	GET_TREE(line->tree, TMP) = free_tree(GET_TREE(line->tree, TMP));
	return (glob);
}

int				expand_glob(t_exp *param, t_ret *ret)
{
	char	*ptr;
	char	*tmp;
	t_slst	*glob;

	ptr = ft_strndup((char *)param->buff + param->i,
		(int)(param->buff_len - param->i));
	tmp = ptr;
	if (ret->word != NULL)
		ptr = ft_strjoin(ret->word, ptr);
	glob = get_exp_glob(ret, ptr, tmp);
	if (ptr != tmp)
		free(ptr);
	free(tmp);
	if (!glob)
		*param->e->ret = 1;
	if (!glob)
		return (ERR_NO_MATCH_FOUND);
	ptr = get_glob_str(glob);
	free_exp_glob(glob);
	expand_free_t_ret(ret, 0);
	param_addstr(ptr, ret);
	param->i = param->buff_len - 1;
	free(ptr);
	return (ERR_NONE);
}
