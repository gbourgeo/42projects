/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nmap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 12:51:06 by frmarinh          #+#    #+#             */
/*   Updated: 2017/09/25 20:56:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"
#include "libft.h"
#include "get_next_line.h"
#include "ft_printf.h"

static void			print_help(char *options[][100])
{
	ft_printf("Usage: ft_nmap [OPTIONS]...\n\n");
	for (int i = 0; options[i][0]; i++) {
		ft_printf("\t--%-10s %s \n", options[i][0], options[i][1]);
	}
	exit(0);
}

static void		get_options(char **argv, char *options[][100])
{
	while (*argv && *++argv) {
		if (ft_strncmp(*argv, "--", 2) != 0)
			nmap_error("%s: Wrong option format: `%s'", globals.progname, *argv);
		char *option = *argv + 2;
		int i;
		for (i = 0; options[i][0]; i++) {
			if (!ft_strcmp(option, options[i][0])) {
				if (i == NM_HELP) 
					globals.flags[i] = "";
				else if (!*(argv + 1) || !ft_strncmp(*(argv + 1), "--", 2))
					nmap_error("%s: Missing parameters: `%s'", globals.progname, *argv);
				else
					globals.flags[i] = *++argv;
				break ;
			}
		}
		if (!options[i][0])
			nmap_error("%s: Illegal option: `%s'", globals.progname, *argv);
	}
}

static void		init_globals(char *prog)
{
	if ((globals.progname = ft_strrchr(prog, '/')) == NULL)
		globals.progname = prog;
	else
		globals.progname++;
	globals.flags = malloc(sizeof(*globals.flags) * NM_OPTIONS_LEN);
	if (globals.flags == NULL)
		nmap_error("%s: malloc failed", globals.progname);
	for (int i = 0; i < NM_OPTIONS_LEN; i++)
		globals.flags[i] = NULL;
	globals.ports_nb = 0;
	ft_memset(globals.ports, 0, MAX_PORTS_SCAN);
	globals.scans_nb = 0;
	globals.scans_types = 0x0000;
	globals.scans = NULL;
	globals.addresses_nb = 0;
	globals.addresses = NULL;
	globals.threads_nb = 0;
	globals.threads = NULL;
	ft_memset(&globals.start, 0, sizeof(globals.start));
}

int				main(int argc, char **argv)
{
	char	*options[][100] = { AVAILABLE_OPTIONS };

	if (argc == 1)
		print_help(options);
	init_globals(argv[0]);
	get_options(argv, options);
	if (globals.flags[NM_HELP])
		print_help(options);
	if (!globals.flags[NM_IP] && !globals.flags[NM_FILE])
		nmap_error("%s: Missing parameter: `--%s or --%s'", globals.progname, options[NM_IP][0], options[NM_FILE][0]);
	get_ports_parameters();
	get_ip_parameters();
	get_threads_parameters();
	get_scans_parameters();
	start_mapping();
	return (0);
}

/*	while (i < argc)
	{
		if ((option = ft_substr(argv[i], 0, 2)) != NULL) {
			if (ft_strlen(argv[i]) > 2 && !ft_strcmp(option, FLAG_SEPARATOR)) {
				if (value) {
					return main_error("Syntax error !", option);
				}
				ft_strdel(&option);
				if ((option = ft_substr(argv[i], 2, ft_strlen(argv[i]))) != NULL) {
					if (!get_flag(option)) {
						add_flag(option);
						if (!single_flag(argv[i], true)) {
							value = true;
						}
					}
					else
						return main_error("flag %s already set !", option);
				}
			} else {
				if (!add_value(argv[i])) {
					return main_error("Syntax error !", option);
				}
				value = false;
			}
			ft_strdel(&option);
		}
		i++;
	}
	initializer();
*/
