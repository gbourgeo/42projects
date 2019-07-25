/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/13 19:07:09 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/03/23 20:58:57 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "libft.h"
# define START 1
# define END 2

typedef struct	s_path
{
	char			*name;
	int				len;
	struct s_path	*next;
}				t_path;

typedef struct	s_link
{
	char			*name;
	struct s_link	*next;
}				t_link;

typedef struct	s_map
{
	int				special;
	int				index;
	char			*name;
	t_link			*links;
	int				linknb;
	struct s_map	*next;
	int				x;
	int				y;
}				t_map;

typedef struct	s_env
{
	int				ants;
	t_map			*rooms;
	t_path			*paths;
}				t_env;

int			ft_init_env(t_env *e);
t_map		*ft_add_room(char **buf, int *special, t_env *e);
int			ft_add_link(char *buf, t_env *e);
int			ft_add_second_link(char *buf, t_env *e);
int			ft_check_paths(t_env *e);
t_path		*ft_get_paths(t_map *start, t_map *rooms, t_path *copy);
void		ft_sort_paths(t_path *paths);
void		ft_print_lem(int ants, char **path);
t_map		*ft_find_room(char *name, t_map *head);
t_map		*find_start_room(t_map *head);
t_map		*find_end_room(t_map *head);
char		*ft_str2join(char const *s1, char const *s2, char const *s3);

#endif
