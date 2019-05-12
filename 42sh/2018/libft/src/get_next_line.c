/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 13:56:40 by rfontain          #+#    #+#             */
/*   Updated: 2019/03/17 19:11:53 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					read_line(int fd, t_list *file)
{
	char	buff[BUFF_SIZE + 1];
	int		n;

	while ((n = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[n] = '\0';
		if (!(file->content = ft_strjoinfree(file->content, buff, 1)))
			return (0);
		if (ft_occuc(buff, CHAR_SEP))
			break ;
	}
	return (1);
}

static t_list		*check_fd(int fd, t_list **file)
{
	t_list		*ret;

	ret = *file;
	while (ret)
	{
		if ((int)ret->content_size == fd)
			return (ret);
		ret = ret->next;
	}
	ret = ft_lstnew("\0", fd);
	ft_lstadd(file, ret);
	ret = *file;
	return (ret);
}

static char			*ft_ralloc(char *str1, char *str2, int n)
{
	if (!(str1 = malloc(n + 1)))
		return (NULL);
	*(str1 + n) = '\0';
	str1 = ft_strncpy(str1, str2, n);
	if (str2)
		free(str2);
	return (str1);
}

int					get_next_line(const int fd, char **line)
{
	static t_list			*file = NULL;
	int						n;
	t_list					*current;
	char					*tmp;
	int						len;

	if (fd < 0 || line == NULL || read(fd, *line, 0) < 0)
		return (-1);
	current = check_fd(fd, &file);
	if (!(read_line(current->content_size, current)))
		return (-1);
	if (!current->content || !(len = (int)ft_strlen(current->content)))
		return (0);
	*line = NULL;
	n = ft_copyuntil(line, current->content, CHAR_SEP);
	if (n < len)
	{
		tmp = ft_strnew(len - (n + 1));
		tmp = ft_strcpy(tmp, (current->content + n + 1));
		free(current->content);
		current->content = ft_ralloc(current->content, tmp, len - n - 1);
	}
	else
		ft_strclr(current->content);
	return (1);
}
