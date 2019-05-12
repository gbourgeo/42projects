/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 05:48:08 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/11 17:41:00 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

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

	max = get_tab_len(*env);
	if (!(tmp = (char**)malloc(sizeof(char*) * (max + len + 1))))
		return (NULL);
	i = -1;
	while ((*env)[++i] && i < max + len)
		tmp[i] = ft_strdup((*env)[i]);
	tmp[i] = NULL;
	free_tab(env);
	return (tmp);
}

int		get_tab_len(char **tabl)
{
	int i;

	i = 0;
	if (tabl)
		while (tabl[i])
			i++;
	return (i);
}
