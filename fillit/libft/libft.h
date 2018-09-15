/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beborch <beborch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 22:46:17 by beborch           #+#    #+#             */
/*   Updated: 2017/12/13 08:34:07 by beborch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

void				*ft_memset(void *s, int c, size_t n);
int					ft_atoi(const char *nptr);
int					ft_isprint(int c);
void				ft_putstr(const char *str);
char				*ft_strdup(const char *src);
size_t				ft_strlen(const char *str);
int					ft_tolower(int c);
int					ft_toupper(int c);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strncpy(char *dest, const char *src, size_t n);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strncat(char *dest, const char *src, size_t n);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strstr(const char *meule_de_foin, const char *aiguille);
void				ft_putchar(char c);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(const char *str, int fd);
void				ft_putendl(const char *s);
void				ft_putendl_fd(const char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putnbr(int n);
char				*ft_strnstr(const char *s1, const char *s2, size_t len);
int					ft_isalpha(int c);
void				ft_striter(char *s, void(*f)(char*));
void				ft_striteri(char *s, void(*f)(unsigned int, char *));
void				ft_strclr(char *s);
void				*ft_memalloc(size_t size);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
char				*ft_strmap(char const *s, char (*f)(char));
int					ft_strequ(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
void				*ft_memdel(void **ap);
char				**ft_strsplit(char const *s, char c);
void				*ft_memmove(void *dest, const void *src, size_t n);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_itoa(int n);
void				ft_bn(void);
void				ft_putbin(char *str);
char				**ft_strtb(char *str);
char				*ft_itb(int nb);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
t_list				*ft_lstnew(const void *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

#endif
