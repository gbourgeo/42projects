/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libfts.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/03 16:52:08 by root              #+#    #+#             */
/*   Updated: 2016/10/10 00:04:06 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTS_H
# define LIBFTS_H

# include <stdlib.h>

void		_ft_bzero(void *s, size_t n);
char		*_ft_strcat(char *dest, const char *src);
int			_ft_isalpha(int c);
int			_ft_isdigit(int c);
int			_ft_isalnum(int c);
int			_ft_isascii(int c);
int			_ft_isprint(int c);
int			_ft_toupper(int c);
int			_ft_tolower(int c);
int			_ft_puts(const char *s);
int			_ft_strlen(const char *s);
void		*_ft_memset(void *s, int c, size_t n);
void		*_ft_memcpy(void *dest, const void *src, size_t n);
char		*_ft_strdup(const char *s);
void		_ft_cat(int fd);
void		*_ft_memchr(const void *s, int c, size_t n);
void		*_ft_memrchr(const void *s, int c, size_t n);
int			_ft_memcmp(const void *s1, const void *s2, size_t n);

#endif
