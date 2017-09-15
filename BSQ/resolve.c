/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 18:57:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/09/15 19:24:25 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void change_map(char **tab, int *found)
{
	int		i;
	int		j;

	j = 0;
	while (j <= found[2])
	{
		i = 0;
		while (i <= found[2])
		{
			tab[found[1] + j][found[0] + i] = 'X';
			i++;
		}
		j++;
	}
}

static int search_o_bis(char **tab, int x, int y, int len)
{
	int		i;
	int		j;

	i = len;
	j = len;
	// Ici on cherche comme ca:
	//  <- <- <-
	// ............
	while (i >= 0)
	{
		if (tab[y + j][x + i] != '.')
			return 0;
		i--;
	}
	// Ici on cherche comme ca:
	// ............ 
	// ............ ^
	// ............ |
	// ............
	i = 0;
	while (j >= 0)
	{
		if (tab[y + j][x + i] != '.')
			return 0;
		j--;
	}
	return (1);
}

static int search_o(char **tab, int x, int y, int len)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	// Ici on cherche comme ca:
	//  -> -> ->
	// ............
	// ............
	// ............
	while (i <= len)
	{
		if (tab[y + j][x + i] != '.')
			return 0;
		i++;
	}
	// Ici on cherche comme ca:
	// ............ 
	// ............ |
	// ............ v
	// ............
	i = len;
	while (j <= len)
	{
		if (tab[y + j][x + i] != '.')
			return 0;
		j++;
	}
	return 1;
}

static void	search_square(char **tab, int x, int y, int *found)
{
	int		len;

	len = 0;
	// Tant qu'on arrive pas a la fin d'une ligne et d'une colonne, on boucle
	// en incrementant la longueur du carré de 1 jusqu'a trouver un 'o'.
	while (tab[y + len] && tab[y][x + len])
	{
		// Jai du decouper search_o en deux fonctions pour la norme:
		if (search_o(tab, x, y, len) == 0)
			break ;
		if (search_o_bis(tab, x, y, len) == 0)
			break ;
		// Si on arrive ici on a pas rencontré de 'o'.
		// Donc on check si la longueur du nouveau carré est plus grande que
		// le carré d'avant.
		// Si oui on stocke sa position (Y, X) puis sa longueur
		// car c'est CE carré le plus grand.
		if (len > found[2])
		{
			found[0] = x;
			found[1] = y;
			found[2] = len;
		}
		// Et on continue...
		len++;
	}
	// Ici on quitte la boucle car on a soit rencontré un 'o',
	// soit on est arrivé a la fin d'une ligne ou d'une colonne
	// (et du coup on peut pas avoir de carré plus grand).
}

void		resolve(char **tab)
{
	// Je crée un tableau d'int pour stocker la position du plus grand carré.
	// A savoir:
	// found[0]:position X du carre.
	// found[1]:position Y du carre.
	// found[2]:longueur des cotés.
	int		found[3]; 
	int		x;
	int		y;

	found[0] = 0;
	found[1] = 0;
	found[2] = 0;
	y = 0;
	// Pour chaque colonne du tableau:
	while (tab[y])
	{
		x = 0;
		// Puis pour chaque ligne du tableau:
		while (tab[y][x])
		{
			// Je calcul la longueur de chaque carré:
			search_square(tab, x, y, found);
			x++;
		}
		y++;
	}
	// On a le plus grand carré. On remplace les '.' par des 'X':
	change_map(tab, found);
}
