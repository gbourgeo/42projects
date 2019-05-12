/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft2.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/06 17:11:14 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/04/06 17:11:30 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT2_H
# define LIBFT2_H

void		ft_print_tables(char **tab);
char		**ft_split(char *str, char *charset);
char		**ft_split_quotes(char *str);
char		**ft_split_whitespaces(char *str);
char		*ft_strcdup(char *str, char c);
char		*ft_strcharset(char *s1, char *s2);
char		*ft_strndup(const char *s1, int size);
char		*ft_strrcdup(char *str, char c);
void		ft_stricpy(char *s1, const char *s2, int pos);
char		*ft_realloc(char *str, int size);
void		ft_deletechar(char *str, int pos);
void		ft_strerror(char *str);
int			ft_open(char *file, int opt, int mod);
int			ft_dup2(int oldd, int newd);
int			ft_close(int fd);
char		*ft_str2join(char const *s1, char const *s2, char const *s3);

#endif
