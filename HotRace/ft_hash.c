/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/15 13:57:54 by gbourgeo          #+#    #+#             */
/*   Updated: 2013/12/15 21:57:42 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

void		ft_hash(t_tree *node)
{
	int		lef;
	int		rig;

	lef = (node->left == NULL) ? -1 : node->hash;
	rig = (node-> right == NULL) ? -1 : node->hash;
	node->hash = 1 + ((lef > rig) ? lef : rig);
}
