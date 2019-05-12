/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_lib.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 09:51:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/25 17:16:40 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_LIB_H
# define SHELL_LIB_H

# include <sys/types.h>

void			sh_freestr(char **str);
void			sh_freetab(char ***table);
char			*sh_get_file(int fd);
char			*sh_getnenv(const char *name, char **env);
char			**sh_getnenvaddr(const char *name, char **env);
int				sh_is_escapable(char c);
char			**sh_newenv(char ***env);
int				sh_putendl_fd(const char *str, int fd);
int				sh_putstr_fd(const char *str, int fd);
int				sh_puttab(const char **env);
int				sh_setenv(char *name, char *value, char ***env);
int				sh_str_isescape(const char *str);
int				sh_stralnum(const char *str);
char			*sh_strchr(const char *str, char c);
int				sh_strncmp(const char *s1, const char *s2, unsigned int n);
char			*sh_strnjoin(const char *s1, const char *s2, size_t len);
char			*sh_strrchr(const char *str, char c);
char			**sh_tabdup(const char **table);
size_t			sh_tablen(const char **table);
void			sh_unsetenv(char *var, char **env);

#endif
