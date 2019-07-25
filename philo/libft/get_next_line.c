/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppellegr <ppellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/02 18:31:11 by ppellegr          #+#    #+#             */
/*   Updated: 2013/12/02 18:31:12 by ppellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		get_next_line(int const fd, char **line)
{
	static char		*str = NULL;
	int				i;

	if (fd == -1)
		return (-1);
	if ((i = ft_buffer_filling(fd, &str)) == -1)
		return (0);
	*line = ft_strsub(str, 0, i);
	str = ft_delete_read_line(str, i + 1);
	return (1);
}

int		ft_checking_new_line(char *s)
{
	int		i;

	i = 0;
	if (s == NULL)
		return (-1);
	while (s[i] != '\n' && s[i] != '\0')
		i++;
	if (s[i] == '\n')
		return (i);
	else
		return (-1);
}

char	*ft_delete_read_line(char *s, int i)
{
	char	*tmp;
	int		j;

	tmp = malloc(sizeof(char *) * (ft_strlen(s) - i));
	j = 0;
	while (s[i] != '\0')
		tmp[j++] = s[i++];
	return (tmp);
}

int		ft_buffer_filling(int const fd, char **str)
{
	char	buf[BUF_SIZE + 1];
	char	*tmp1;
	int		ret;
	int		i;

	ret = 1;
	while (ret != 0 && ((i = ft_checking_new_line(*str)) == -1))
	{
		ret = read(fd, buf, BUF_SIZE);
		buf[ret] = '\0';
		tmp1 = *str;
		if (*str == NULL)
			*str = ft_strdup(buf);
		else
			*str = ft_strjoin(*str, buf);
		if (tmp1 != NULL)
			free(tmp1);
	}
	if (ret == 0 && i == -1 && ft_strcmp("", *str))
	{
		*str = ft_strjoin(*str, "\n");
		i = (ft_strlen(*str) - 1);
	}
	return (i);
}
