/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 16:12:33 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/13 04:26:21 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "ft_printf.h"

static void		corewar_usage(char *progname)
{
	ft_dprintf(2, "Usage : %s [-hv] [-p [nb_cycle,...]] ", progname);
	ft_dprintf(2, "[-dump nbr_cycles] [[-n number] champ1.cor] ...\n\n");
	ft_dprintf(2, "\t-h\t\t\t: ");
	ft_dprintf(2, "Display this help then exits.\n");
	ft_dprintf(2, "\t-v\t\t\t: ");
	ft_dprintf(2, "Graphical mode (ncurses).\n");
	ft_dprintf(2, "\t-p number,...\t\t: ");
	ft_dprintf(2, "Execute 'nb_cycles' then stops. You can give multiple ");
	ft_dprintf(2, "values separated by comas with no spaces in between.\n");
	ft_dprintf(2, "\t\t\t\t  Works only on graphical mode.\n");
	ft_dprintf(2, "\t-d, -dump nbr_cycles\t: ");
	ft_dprintf(2, "Dumps memory after 'nbr_cycles' cycles then exits.\n");
	ft_dprintf(2, "\t-n number\t\t: ");
	ft_dprintf(2, "Fix a number to player. If missing, the player will ");
	ft_dprintf(2, "have the first available number.\n");
}

static void		corewar_print_error(const char *str, char *arg, char *progname)
{
	ft_dprintf(2, "%s: %s", progname, str);
	if (arg && str[ft_strlen(str) - 1] != '\n')
		ft_dprintf(2, " `%s'", arg);
	ft_dprintf(2, "\n");
	if (*str == '-')
		corewar_usage(progname);
}

void			corewar_errors(int errnb, char *arg, t_env *e)
{
	static const char	*error[] = {
		"-- missing argument.\n", "-- unknown argument", "-- help\n",
		"value must contain only numbers", "wrong value",
		"invalid filename", "too many champions received",
		"number already taken", "-- missing champion.\n",
		"impossible to open file", "impossible to lseek file for",
		"malloc failed", "read failed",
		"champion: size too small for", "champion: invalid header for",
		"champion: champion size differ from header for",
		"champion: size too big for",
		"ncurses: Failed to init main Window.\n",
		"ncurses: Failed to init arena Window Box.\n",
		"ncurses: Failed to init arena Window.\n",
		"Failed to init info Window Box.\n", "Failed to init champ Window.\n",
		"Failed to init VM Window.\n", "Failed to init info Window.\n",
		"wgetch returned -1.\n",
	};

	if (errnb > 0 && errnb <= (int)(sizeof(error) / sizeof(error[0])))
		corewar_print_error(error[errnb - 1], arg, e->progname);
}
