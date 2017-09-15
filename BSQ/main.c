/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 16:45:09 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/09/15 19:15:42 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void print_map(char **tab)
{
	int i;
	int j;

	j = 0;
	while (tab[j])
	{
		i = 0;
		while (tab[j][i])
			write(1, &tab[j][i++], 1);
		write(1, "\n", 1);
		j++;
	}
}

int main(int ac, char ** av)
{
	int fd;
	char *map;
	char **tab;

	if (ac != 2)
		return 1;
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return 1;
	// On recupere le contenu du fichier et on stocke tout ca dans un (char *):
	if ((map = get_map(fd, NULL)) == NULL)
		return 1;
	close(fd);
	// On convertit notre string (char *) en tableau (char **):
	if ((tab = get_tab(map)) == NULL)
		return 1;
	// Algorythme de recherche:
	resolve(tab);
	// Affichage de la map:
	print_map(tab);
	return 0;
}
