/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 22:15:33 by dbaffier          #+#    #+#             */
/*   Updated: 2019/11/02 21:22:59 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "asm.h"
#include "cw_hexdump.h"

static int	err_file(int err)
{
	static char *tab_err[] = { NULL, ERR_STR_FILE,
		ERR_STR_EXTENSION, ERR_STR_NOFILE, ERR_STR_OVERFLOW, ERR_STR_OPEN};

	ft_dprintf(2, "%s\n", tab_err[err]);
	if (err != 6)
		ft_dprintf(2, "Usage : ./asm file.s\n");
	return (1);
}

int			main(int ac, char **av)
{
	t_env		e;
	int			ret;
	int			i;

	ft_memset(&e, 0, sizeof(e));
	i = parse_flag(&e, av, 1);
	parse_narg(&e, ac, i);
	if (e.flag & FLAG_D)
		return (deasm(&e, av, i));
	i = get_user_entry(&e, av, i);
	if ((ret = asm_file(ac, av, i)) > 0)
	{
		if (e.fd_user)
			free(e.fd_user);
		return (err_file(ret));
	}
	if ((ret = parser(&e, av[i])) > 0)
		return (err_file(ret));
	if ((ret = dump_to_file(&e)) > 0)
		return (err_file(ret));
	free_aolist(e.aolist);
	return (0);
}
