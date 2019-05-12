/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tmp_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 15:51:50 by rfontain          #+#    #+#             */
/*   Updated: 2019/03/14 17:30:08 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_lib.h"
#include "libft.h"
#include "put.h"
#include "shell.h"

static char	*chr_beg_glob(char *buff)
{
	char	*ptr;
	int		i;

	ptr = buff;
	i = -1;
	while (buff[++i])
		if (buff[i] == '/')
			ptr = &buff[i];
		else if (ft_strchr("*[?", buff[i]))
			break ;
	return (ptr);
}

static char	*get_flag(char *tmp, int glob)
{
	char	*flag;
	char	*stmp;

	if (glob)
		flag = chr_beg_glob(tmp);
	else if (!(flag = sh_strrchr(tmp, '/')))
		flag = ft_strchr(tmp, 0);
	while (flag != tmp && *(flag - 1) == '/')
		flag--;
	if (flag != tmp)
		stmp = ft_strndup(tmp, flag - tmp);
	else
		stmp = ft_strndup(tmp, flag - tmp + 1);
	return (stmp);
}

static char	*get_stmp(char *stmp, char *tmp, int glob)
{
	if (*stmp != '/')
	{
		if (*stmp == '~')
			tmp = replace_tilde(stmp, getenv("HOME"));
		if (*stmp == '~')
			stmp = get_flag(tmp, glob);
		else
			stmp = get_flag(stmp, glob);
	}
	else
		stmp = get_flag(stmp, glob);
	if (tmp)
		free(tmp);
	return (stmp);
}

t_tree		*set_tmp(char *buff, int glob)
{
	t_tree	*file;
	char	*stmp;
	char	*tmp;

	if (!(stmp = sh_strrchr(buff, ' ')))
		stmp = buff;
	else
		stmp += 1;
	tmp = NULL;
	stmp = get_stmp(stmp, tmp, glob);
	if (glob)
	{
		if ((stmp[0] != '/' || stmp[1]))
			tmp = ft_strjoin(stmp, "/");
		else
			tmp = ft_strdup(stmp);
	}
	else
		tmp = NULL;
	file = create_file_tree(stmp, tmp, NULL);
	free(stmp);
	if (tmp)
		free(tmp);
	return (file);
}
