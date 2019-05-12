/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 23:07:03 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/28 17:53:02 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __LIBFT_H
# define __LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <fcntl.h>

# define BUFF_SIZE 32
# define CHAR_SEP '\n'

# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN    "\x1b[36m"
# define WHITE   "\x1b[1;37;40m"
# define RESET   "\x1b[0m"
# define ERROR   "\x1b[90m"

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memset(void *s, int c, size_t n);
int					ft_atoi(const char *str);
int					ft_bzero(void *s, size_t n);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_isascii(int c);
int					ft_isspace(int c);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strdup(const char *str);
size_t				ft_strlen(const char *str);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strncat(char *dest, const char *src, size_t n);
size_t				ft_strlcat(char *dest, const char *src, size_t n);
int					ft_strncmp(const char *s1, const char *s2, unsigned int n);
char				*ft_strncpy(char *dest, const char *src, size_t n);
char				*ft_strnew(size_t size);
char				*ft_strnstr(const char *str, const char *to_find,
		size_t len);
char				*ft_strchr(const char *str, int c);
char				*ft_strrchr(const char *str, int c);
char				*ft_strstr(const char *str, const char *to_find);
int					ft_tolower(int c);
int					ft_toupper(int c);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *str);
void				ft_striter(char *str, void (*f)(char *));
void				ft_striteri(char *str, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
void				ft_putchar(char c);
void				ft_putstr(const char *str);
void				ft_putendl(char const *str);
void				ft_putnbr(int nb);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(const char *str, int fd);
void				ft_putendl_fd(const char *str, int fd);
void				ft_putnbr_fd(int nb, int fd);
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void*, size_t));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
int					ft_occuc(char *str, int c);
void				ft_lstadd_back(t_list *alst, t_list *new);
void				ft_putstrstr(char **str, char c);
void				ft_putstrstr_fd(char **str, char c, int fd);
void				ft_strrev(char *str);

char				*ft_strjoinch(char *s1, char c);
int					ft_copyuntil(char **dst, char *src, char c);
char				*ft_strjoinfree(char *s1, char *s2, int i);

int					ft_for(int i, int delimiter, int inc);
char				*ft_strup(char *str, size_t size);
char				*ft_strlow(char *str, size_t size);

char				*ft_itoa_base(int nb, int base);
char				*ft_convert_base(int nb, int base, int i);
int					ft_nblen_base(unsigned int nb, int base);

int					read_line(int fd, t_list *file);
int					get_next_line(int fd, char **line);

int					ft_abs(int n);
void				ft_putend(char *str, char *end);
void				ft_putnbend(int nb, char *str);
void				ft_putendnb(char *str, int nb);

char				**ft_strsplit_ws(char const *s);
void				ft_find(char *src, char *to_find, int *beg, int *end);

void				ft_putstr_cl(char *str, char *color);
void				ft_putnbr_cl(int nb, char *color);
void				ft_putendl_cl(char *str, char *color);
void				ft_putend_cl(char *str1, char *color1, char *str2,
		char *color2);

int					ft_strlen_ch(char *str, char c);
char				*strdup_until(char *old, char c);
void				*ft_free(void *targ, void *ret);
char				*strnjoin(char *str1, char *str2, int n);
char				*stercat(char *src1, char *src2, char *dest);
char				*ft_strnchr(const char *str, char c, int n);
char				*ft_strndup(char *str, int nb);
void				ft_putchars(char c, int nb);

#endif
