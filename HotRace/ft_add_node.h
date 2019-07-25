/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_node.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/15 02:11:26 by gbourgeo          #+#    #+#             */
/*   Updated: 2013/12/15 16:37:05 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		FT_ADD_NODE_H
# define	FT_ADD_NODE_H
# include <stdlib.h>

typedef struct		s_list
{
	char			*keyw;
	char			*value;
	int				hash;
	struct s_list	*left;
	struct s_list	*right;
}					t_list;

t_list		*ft_add_node(t_list **t, int h, const char *k, const char *v);
static int	find_null_node(t_list *tmp, t_list *node);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strdup(const char *s1);
void		ft_putstr(const char *str);

#endif		/* FT_ADD_NODE_H */
