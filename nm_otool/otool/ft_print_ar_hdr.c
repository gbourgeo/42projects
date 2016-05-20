/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ar_hdr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/12 01:27:44 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/20 04:31:28 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static char			*ft_fill_buf(struct ar_hdr *ar_hdr, int size, int ref)
{
	char			*buf;
	int				i;

	buf = malloc(sizeof(char) * (size + 1));
	if (buf == NULL)
		return (NULL);
	if (ref == 0)
		ft_memcpy(buf, ar_hdr->ar_mode, size);
	else if (ref == 1)
		ft_memcpy(buf, ar_hdr->ar_uid, size);
	else if (ref == 2)
		ft_memcpy(buf, ar_hdr->ar_gid, size);
	else if (ref == 3)
		ft_memcpy(buf, ar_hdr->ar_size, size);
	else if (ref == 4)
		ft_memcpy(buf, ar_hdr->ar_date, size);
	i = size - 1;
	while (i >= 0 && buf[i] == ' ')
		buf[i--] = '\0';
	buf[size] = '\0';
	return (buf);
}

static void			ft_print_spaces(int len, char c, char *buf)
{
	int				i;

	i = ft_strlen(buf);
	if (c == '/' || len == 5)
	{
		while (len - i++ > 0)
			ft_putchar(' ');
		ft_putstr(buf);
	}
	else
	{
		ft_putstr(buf);
		while (len - i++ > 0)
			ft_putchar(' ');
	}
	ft_putchar(c);
}

void				ft_print_ar_hdr(struct ar_hdr *ar_hdr)
{
	char			*buf;
	int				i;

	buf = ft_fill_buf(ar_hdr, sizeof(ar_hdr->ar_mode), 0);
	ft_putchar('0');
	ft_print_spaces(0, ' ', buf);
	free(buf);
	buf = ft_fill_buf(ar_hdr, sizeof(ar_hdr->ar_uid), 1);
	ft_print_spaces(3, '/', buf);
	free(buf);
	buf = ft_fill_buf(ar_hdr, sizeof(ar_hdr->ar_gid), 2);
	ft_print_spaces(3, ' ', buf);
	free(buf);
	buf = ft_fill_buf(ar_hdr, sizeof(ar_hdr->ar_size), 3);
	ft_print_spaces(5, ' ', buf);
	free(buf);
	buf = ft_fill_buf(ar_hdr, sizeof(ar_hdr->ar_date), 4);
	ft_print_spaces(0, ' ', buf);
	free(buf);
	i = 0;
	while (ar_hdr->ar_name[i] && ar_hdr->ar_name[i] != ' ')
		i++;
	write(1, ar_hdr->ar_name, i);
	ft_putchar('\n');
}
