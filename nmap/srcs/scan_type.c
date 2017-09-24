/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 16:45:32 by frmarinh          #+#    #+#             */
/*   Updated: 2017/09/12 16:45:38 by frmarinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static t_scan_type		*alloc_scan_type(char *name)
{
	t_scan_type		*alloc = NULL;
	if (!(alloc = (t_scan_type*)malloc(sizeof(struct s_scan_type))))
		return (NULL);
	alloc->name = ft_strdup(name);
	alloc->next = NULL;
	return (alloc);
}

static t_scan_type		*add_scan_type(t_scan_type *scans, t_scan_type *new)
{
	if (new) {
		while (scans->next)
			scans = scans->next;
		scans->next = new;
	}
}

static t_scan_type		*get_all_scans_type()
{
	t_scan_type		*scans = alloc_scan_type("SYN");
	if (scans) {
		add_scan_type(scans, alloc_scan_type("NULL"));
		add_scan_type(scans, alloc_scan_type("FIN"));
		add_scan_type(scans, alloc_scan_type("XMAS"));
		add_scan_type(scans, alloc_scan_type("ACK"));
		add_scan_type(scans, alloc_scan_type("UDP"));
	}
	return (scans);
}

static bool				valid_scan_type(t_scan_type *scans, char *type)
{
	while (scans)
	{
		if (!ft_strcmp(scans->name, type)) {
			return (true);
		}
		scans = scans->next;
	}
	return (false);
}

bool					load_scans_type(t_nmap *nmap)
{
	t_scan_type		*scans = get_all_scans_type();
	t_flag			*flag = get_flag("scan");
	t_scan_type		*customs = NULL;

	if (scans) {
		if (flag != NULL && flag->value != NULL) {
			char	**types = ft_strsplit(flag->value, '/');
			if (types) {
				int i  = 0;
				while (types[i]) {
					if (valid_scan_type(scans, types[i])) {
						if (!customs) {
							customs = alloc_scan_type(types[i]);
						} else {
							add_scan_type(customs, alloc_scan_type(types[i]));
						}
					} else {
						printf("ft_nmap: Unknown scan type %s\n");
						return (false);
					}
					i++;
				}
			}
		}
		nmap->scans = (customs) ? customs : scans;
		return (true);
	}
	return (false);
}
