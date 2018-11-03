/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   users.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 06:30:49 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/10/31 09:06:55 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

struct s_usr	*users = NULL;

static t_usr	*new_user(char *name, t_usr *prev)
{
	t_usr		*new;

	new = malloc(sizeof(*new));
	if (!new)
		return NULL;
	new->prev = prev;
	strncpy(new->name, name, NICK_CLIENTS);
	new->next = NULL;
	return new;
}

void			add_user(char *name)
{
	if (users == NULL) {
		users =  new_user(name, NULL);
		return ;
	}
	for (t_usr *ptr = users; ptr; ptr = ptr->next) {
		if (ptr->next == NULL) {
			ptr->next = new_user(name, ptr);
			break ;
		}
	}
}

void			del_user(char *name)
{
	if (users == NULL)
		return ;
	for (t_usr *ptr = users; ptr; ptr = ptr->next) {
		if (strcmp(ptr->name, name))
			continue ;
		if (ptr->prev == NULL)
			users = ptr->next;
		if (ptr->prev)
			ptr->prev->next = ptr->next;
		if (ptr->next)
			ptr->next->prev = ptr->prev;
		memset(ptr, 0, sizeof(*ptr));
		free(ptr);
	}
}

void			clear_users()
{
	t_usr		*next;

	while (users)
	{
		next = users->next;
		memset(users, 0, sizeof(*users));
		free(users);
		users = next;
	}
}

void			parse_users(char *buf, int pos)
{
	clear_users();
	for (size_t i = pos, j = 0; buf[i]; i = j, pos = i) {
		for (j = i; buf[j] && buf[j] != ' '; j++)
			;
		buf[j] = '\0';
		add_user(&buf[i]);
		buf[j] = ' ';
		for (; buf[j] && buf[j] == ' '; j++)
			;
	}
	strcpy(buf, buf + pos + 1);
}

void			aff_users(t_ncu *n)
{
	wclear(n->usersWin);
	for (t_usr *ptr = users; ptr; ptr = ptr->next) {
		wprintw(n->usersWin, "%s\n", ptr->name);
	}
	wrefresh(n->usersWin);
}

void			send_users(const char *key, t_cl *cl)
{
	char		buf[BUF_CLIENTS];
	int			len;

	memset(buf, 0, BUF_CLIENTS);
	strcpy(buf, key);
	for (t_usr *ptr = users; ptr; ptr = ptr->next) {
		strcat(buf, ptr->name);
		strcat(buf, " ");
	}
	len = strlen(buf);
	buf[len - 1] = '\0';
	for (int i = 1; i < MAX_CLIENTS; i++) {
		if (cl[i].fd)
			write(cl[i].fd, buf, len + 1);
	}
}