/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_hexdump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 18:03:52 by mmonier           #+#    #+#             */
/*   Updated: 2019/10/23 03:54:27 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

static void		print_head(t_data *data)
{
	char		c;
	int			pause;

	pause = 0;
	while (1)
	{
		if (pause == 0)
		{
			print_file_name(data);
			print_dot(data);
			print_compilation(data);
			pause = 1;
		}
		if ((c = wgetch(data->main_win)) == '\n')
			break ;
	}
}

static int		cw_hexdump(t_data *data, char *file)
{
	if (!(data->e->flag & FLAG_S) && !(data->e->flag & FLAG_F))
		if ((data->fd = create_corfile(data, file)) < 0)
			return (ERR_OPEN);
	if (data->e->flag & FLAG_N)
		print_head(data);
	way_to_corewar(data, data->ao);
	return (0);
}

static int		init_data(t_data *data, t_env *e)
{
	int ret;

	data->e = e;
	data->ao = e->aolist;
	if (data->e->flag & FLAG_S || data->e->flag & FLAG_F)
		if ((ret = user_file(data)) != 0)
			return (ret);
	return (0);
}

int				dump_to_file(t_env *e)
{
	t_data	data;
	int		ret;

	ft_memset(&data, 0, sizeof(t_data));
	if (e->flag & FLAG_N)
		init_screen(&data);
	if ((ret = init_data(&data, e)) != 0)
		return (ret);
	cw_hexdump(&data, e->fd_name);
	if (e->flag & FLAG_N)
	{
		print_menu(&data);
		print_hex(&data);
		print_end(&data);
		endwin();
	}
	if ((e->flag & FLAG_O) && !(e->flag & FLAG_N))
		print_fsize(&data);
	if ((e->flag & FLAG_P) || (e->flag & FLAG_GP))
		print_path(&data);
	close(data.fd);
	free(data.file_name);
	return (0);
}
