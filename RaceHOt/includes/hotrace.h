/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotrace.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/14 22:23:27 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/08/02 23:02:36 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOTRACE_H
# define HOTRACE_H

# include <stdlib.h>

typedef struct		s_list
{
	char			*keyw;
	char			*value;
	struct s_list	*left;
	struct s_list	*right;
}					t_list;

int					get_next_line(int const fd, char **line);
t_list				*ft_add_node(t_list **tree, char *key, char *value);
int					ft_search_node(t_list *tree, char *key);
void				ft_putstr(const char *str);

#endif
