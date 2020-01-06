/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 17:02:15 by mmonier           #+#    #+#             */
/*   Updated: 2019/10/23 03:54:54 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"
#include "asm.h"

static int	count_moveup(char *file, char *dotdot)
{
	int i;
	int j;
	int count;

	i = 0;
	j = 0;
	count = 0;
	while (file[i])
	{
		if (file[i] == '.')
		{
			j = 0;
			while (dotdot[j] == file[i])
			{
				j++;
				i++;
			}
			if (j == 4)
				count++;
		}
		i++;
	}
	return (count);
}

static void	check_if_dir(t_data *data, int i)
{
	int			j;
	static char	buff[4096];

	j = 0;
	while (data->file_name[i])
	{
		buff[j] = data->file_name[i];
		j++;
		i++;
	}
	if (buff[0] != '\0')
	{
		free(data->file_name);
		data->file_name = ft_strdup(buff);
	}
}

static void	trunc_dir(t_data *data, int count_trunc)
{
	int			len;
	int			i;
	static char buff[4096];

	getcwd(buff, 4096);
	len = ft_strlen(buff) - 1;
	i = count_trunc * 3;
	while (buff[len])
	{
		if (count_trunc == 0)
			break ;
		else
			buff[len] = '\0';
		if (buff[len] == '/')
			count_trunc--;
		len--;
	}
	check_if_dir(data, i);
	data->file_name = ft_strjoinfree(buff, data->file_name, 2);
}

void		handle_dotdot(t_data *data)
{
	if (ft_strcmp(data->file_name, ".") == 0)
	{
		free(data->file_name);
		data->file_name = getcwd(NULL, 0);
	}
	if (ft_strcmp(data->file_name, "../") == 0
			|| ft_strcmp(data->file_name, "..") == 0
			|| count_moveup(data->file_name, "../") > 0)
		trunc_dir(data, count_moveup(data->file_name, "../"));
}

char		*cut_path(char *file)
{
	int		len;
	int		len_p;
	int		i;
	char	*without_path;

	len = ft_strlen(file);
	len_p = len_path(file);
	i = 0;
	if (!(without_path = (char *)malloc(sizeof(char) * (len - len_p) + 1)))
		return (NULL);
	while (file[len_p])
	{
		without_path[i] = file[len_p];
		i++;
		len_p++;
	}
	without_path[i] = '\0';
	free(file);
	return (without_path);
}
