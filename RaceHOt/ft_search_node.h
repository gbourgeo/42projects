/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_node.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/15 05:39:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2013/12/15 11:56:14 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		FT_SEARCH_NODE_H
# define	FT_SEARCH_NODE_H

typedef struct		s_list
{
	char			*keyw;
	char			*value;
	struct s_list	*left;
	struct s_list	*right;
}					t_list;

int			ft_search_node(t_list *result, char *key);
void		ft_putstr(char const *str);
int			ft_strcmp(const char *s1, const char *s2);

#endif		/* FT_SEARCH_NODE_H */
