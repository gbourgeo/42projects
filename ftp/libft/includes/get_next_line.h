/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/03 22:15:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/04/21 17:41:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 8

# include "libft.h"
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

typedef struct		s_gnl
{
	int				fd;
	char			*copy;
	struct s_gnl	*next;
	struct s_gnl	*prev;
}					t_gnl;

int					get_next_line(int const fd, char **line);

#endif
