/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/15 20:09:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2013/12/15 21:59:33 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

t_tree		*ft_add_node(t_tree *t, char *k, char *v)
{
	if (t == NULL)
		return (ft_create_node(k, v, NULL, NULL));
	if (k < t->keyw)
		t->left = ft_add_node(t->left, k, v);
	else if (k > a->keyw)
		t->right = ft_add(t->right, k, v);
	else
		t->value = value;
	return (ft_shake_tree(t));
}
