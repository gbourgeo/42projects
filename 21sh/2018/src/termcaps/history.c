/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 04:43:32 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/03 20:59:11 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"
#include "shell_term.h"
#include "history.h"
#include "shell_lib.h"

static void		get_lines(t_hist **begin, int fd)
{
	char	*line;
	char	*chr;

	line = sh_get_file(fd);
	if (line)
	{
		if (!(*begin = ft_memalloc(sizeof(t_hist))))
			return ;
		(*begin)->content = strdup_until(line, '\n');
		(*begin)->c_size = ft_strlen((*begin)->content);
		chr = line;
		while ((chr = ft_strchr(chr, '\n')))
		{
			chr += 1;
			if (!((*begin)->prev = ft_memalloc(sizeof(t_hist))))
				break ;
			(*begin)->prev->next = (*begin);
			(*begin)->prev->content = strdup_until(chr, '\n');
			(*begin)->prev->c_size = ft_strlen((*begin)->prev->content);
			(*begin) = (*begin)->prev;
		}
		free(line);
	}
}

void			create_hist(t_hist **begin, char **env)
{
	t_hist	*curr;
	int		fd;
	char	*path;

	if (!(path = get_env(env, "HOME")))
		fd = open(TMP_PATH, O_RDWR | O_APPEND | O_CREAT, 0644);
	else
	{
		path = ft_strjoinfree(path, "/", 1);
		path = ft_strjoinfree(path, HIST_NAME, 1);
		fd = open(path, O_RDWR | O_APPEND | O_CREAT, 0644);
		free(path);
	}
	get_lines(begin, fd);
	curr = *begin;
	while (curr)
	{
		curr->begin = *begin;
		curr = curr->next;
	}
	close(fd);
}

static t_hist	*fill_hist(char *buff, int fd)
{
	int		i;
	t_hist	*curr;

	i = 0;
	while (buff[i] && buff[i] != '\n')
		ft_putchar_fd(buff[i++], fd);
	ft_putchar_fd('\n', fd);
	if (!(curr = ft_memalloc(sizeof(t_hist))))
		return (NULL);
	if (!(curr->content = strdup_until(buff, '\n')))
	{
		free(curr);
		return (NULL);
	}
	curr->c_size = ft_strlen_ch(buff, '\n');
	curr->begin = curr;
	return (curr);
}

static void		get_new_hist(t_hist **curr, char *buff, int fd)
{
	if (*curr)
	{
		if (ft_strcmp(buff, (*curr)->begin->content) != 0)
		{
			(*curr) = (*curr)->begin;
			if (!((*curr)->prev = fill_hist(buff, fd)))
				return ;
			(*curr)->prev->next = *curr;
			(*curr) = (*curr)->prev;
			while ((*curr)->next)
			{
				if ((*curr)->tmp)
					free((*curr)->tmp);
				(*curr)->tmp = NULL;
				if ((*curr)->prev)
					(*curr)->begin = (*curr)->prev->begin;
				*curr = (*curr)->next;
			}
			*curr = (*curr)->prev;
		}
		*curr = (*curr)->begin;
	}
	else
		*curr = fill_hist(buff, fd);
}

void			save_history(t_line *line, char *buff, t_hist **curr,
		char **env)
{
	int		fd;
	char	*path;

	if (!(path = get_env(env, "HOME")))
		fd = open(TMP_PATH, O_RDWR | O_APPEND | O_CREAT, 0644);
	else
	{
		path = ft_strjoinfree(path, "/", 1);
		path = ft_strjoinfree(path, HIST_NAME, 1);
		fd = open(path, O_RDWR | O_APPEND | O_CREAT, 0644);
		free(path);
	}
	get_new_hist(curr, buff, fd);
	close(fd);
	(void)line;
}
