/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 07:14:04 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/23 07:42:09 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"
#include "shell_lib.h"

void	put_prompt(char *prompt, int col)
{
	ft_putstr_fd(RESET, STDERR_FILENO);
	if (col)
		ft_putstr_fd(RED, STDERR_FILENO);
	else
		ft_putstr_fd(GREEN, STDERR_FILENO);
	ft_putstr_fd(prompt, STDERR_FILENO);
	ft_putstr_fd(RESET, STDERR_FILENO);
}

char	*get_line(int fd)
{
	char	buff[4097];
	int		nb_read;
	int		i;

	nb_read = read(fd, buff, 4097);
	buff[nb_read] = '\0';
	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	buff[i] = '\0';
	if (buff[0])
		return (ft_strdup(buff));
	else
		return (NULL);
}

void	free_tab(char ***tabl)
{
	int i;

	i = -1;
	if (*tabl)
	{
		while ((*tabl)[++i])
			free((*tabl)[i]);
		free(*tabl);
	}
}

char	**ft_ralloc(char ***env, int len)
{
	char	**tmp;
	int		i;
	int		max;

	max = sh_tablen((const char **)*env);
	if (!(tmp = (char**)malloc(sizeof(char*) * (max + len + 1))))
		return (NULL);
	i = -1;
	while ((*env)[++i] && i < max + len)
		tmp[i] = ft_strdup((*env)[i]);
	tmp[i] = NULL;
	free_tab(env);
	return (tmp);
}

void	get_tmp_buff(char **buff, char **buff_tmp, int to_free)
{
	size_t	len;
	size_t	max_len;

	max_len = MAX_SHELL_LEN;
	len = ft_strlen(*buff_tmp);
	free(*buff);
	if (!(*buff = ft_memalloc(sizeof(char)
					* (max_len * (len / max_len + 1)) + 1)))
		return ;
	ft_strcpy(*buff, *buff_tmp);
	if (to_free)
	{
		free(*buff_tmp);
		*buff_tmp = NULL;
	}
}
