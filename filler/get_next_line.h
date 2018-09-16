/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/03 22:15:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/01/26 23:11:18 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 128

# include "libft.h"
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

int			get_next_line(int const fd, char ** line);
static int	create_line(int const fd, char **line);
static int	check_copy(char **line, char **copy);
static int	analyse_line(char **line, char **copy);

#endif
