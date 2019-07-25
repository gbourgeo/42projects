/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/03 22:15:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2013/12/15 21:25:19 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		GET_NEXT_LINE_H
# define	GET_NEXT_LINE_H
# define	BUFF_SIZE 128

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>

int			get_next_line(int const fd, char ** line);
static char	*fill_line(char *tmp, size_t *i);
static char	*create_tmp(int const fd, char *fd_tmp);
char		*ft_memalloc(size_t size);
char		*ft_strjoin(char const *s1, char const *s2);

#endif
