/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deasm_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 00:23:29 by mmonier           #+#    #+#             */
/*   Updated: 2019/10/03 17:39:42 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deasm.h"

static void		without_encoding_byte(t_info *inf)
{
	inf->decode = DS_PARAM;
	inf->type[0] = TYPE_DIR;
	inf->size[0] = inf->dir_size;
	inf->n_param = 1;
}

static void		dswrite_instructions(t_info *inf, char buff)
{
	unsigned int cast;

	cast = (unsigned int)buff;
	if (inf->cursor == 2191)
	{
		ft_dprintf(inf->ds_fd, "\n\n");
		inf->decode = OPC;
	}
	else if (inf->decode == OPC)
	{
		dswrite_opc(inf, buff);
		if (buff == 1 || buff == 9 || buff == 12 || buff == 15)
			without_encoding_byte(inf);
		else
			inf->decode = E_BYTE;
	}
	else if (inf->decode == E_BYTE)
	{
		decode_types(inf, cast);
		inf->decode = DS_PARAM;
	}
	else if (inf->decode == DS_PARAM)
		dswrite_param(inf, buff);
}

static void		dswrite(t_info *inf, char buff)
{
	if (inf->cursor >= 132 && inf->cursor < 140)
		return ;
	if (inf->cursor == 4)
		ft_dprintf(inf->ds_fd, ".name \"");
	if (inf->cursor == 140)
		ft_dprintf(inf->ds_fd, "\"\n.comment \"");
	if (buff != 0x0)
		ft_dprintf(inf->ds_fd, "%c", buff);
	inf->decode = END;
}

static int		init_read(t_info *i)
{
	int ds;

	if ((ds = open(i->ds_name, O_CREAT | O_TRUNC | O_RDWR, 0700)) == -1)
		return (DS_ERR_OPEN);
	i->ds_fd = ds;
	lseek(i->fd, 4, SEEK_SET);
	i->cursor = 4;
	dswrite_warning(i);
	return (0);
}

int				deasm_file(t_info *inf)
{
	unsigned char	buff;

	if (init_read(inf) == DS_ERR_OPEN)
		return (DS_ERR_OPEN);
	while (read(inf->fd, &buff, 1) > 0)
	{
		if (inf->cursor < 2191)
			dswrite(inf, buff);
		if (inf->cursor >= 2191)
		{
			if (inf->decode == END)
			{
				ft_dprintf(inf->ds_fd, "\"");
				inf->decode = OPC;
			}
			dswrite_instructions(inf, buff);
		}
		inf->cursor = inf->cursor + 1;
	}
	return (0);
}
