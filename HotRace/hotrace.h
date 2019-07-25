/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotrace.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/14 22:23:27 by gbourgeo          #+#    #+#             */
/*   Updated: 2013/12/15 21:58:49 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		HOTRACE_H
# define	HOTRACE_H
# define	SIZE_N(a) ((a == NULL) ? -1 : a->height)
# include <stdlib.h>

typedef struct		s_tree
{
	char			*keyw;
	char			*value;
	int				hash;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;

int		get_next_line(int const fd, char ** line);
t_tree	*ft_create_node(char *k, char *v, t_tree *left, t_tree *right);
t_tree	*ft_add_node(t_tree *t, char *k, char *v);
t_tree	*ft_shake_tree(char *keyw, char *value, t_tree *node);
void	ft_hash(t_tree *node);
int		ft_search_node(t_tree *tree, char *key);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_putstr(char *str);

#endif		/* HOTRACE_H */
