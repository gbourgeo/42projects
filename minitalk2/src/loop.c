/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 06:33:27 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/10/30 06:31:08 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static char			*strjoin(const char *s1, const char *s2)
{
	char			*ret;

	ret = malloc(strlen(s1) + strlen(s2) + 1);
	if (ret == NULL)
		return NULL;
	strcpy(ret, s1);
	strcat(ret, s2);
	return ret;
}

static int 			init_select(int server, int size, fd_set *fdr, fd_set *fdw)
{
	int 			max;

	max = server;
	FD_ZERO(fdr);
	FD_ZERO(fdw);
	if (server)
		FD_SET(server, fdr);
	for (int i = 0; i < size; i++) {
		if (clients[i].fd == -1 || clients[i].leaved)
			continue ;
		FD_SET(clients[i].fd, fdr);
		if (clients[i].wr[0])
			FD_SET(clients[i].fd, fdw);
		if (clients[i].fd > max)
			max = clients[i].fd;
	}
	return max;
}

static void				accept_connection(int server)
{
	int					fd;

	fd = accept(server, NULL, NULL);
	if (fd < 0) {
		clients[0].leaved = 1;
		return ;
	}
	for (int i = 0; i < MAX_CLIENTS; i++) {
		if (clients[i].fd != -1)
			continue ;
		clear_clients(&clients[i], 1);
		clients[i].fd = fd;
		strcpy(clients[i].wr, "Connected: ");
		for (int j = 0; j < MAX_CLIENTS; j++) {
			if (clients[j].fd == -1)
				continue ;
			strcat(clients[i].wr, clients[j].user);
		}
		strcat(clients[i].wr, "\n");
		write(clients[i].fd, clients[i].wr, strlen(clients[i].wr));
		return ;
	}
	write(fd, "Server Full\n", 12);
	close(fd);
}

static void				read_in(int i)
{
	int					j = 0;
	int					len = 0;
	int					ch;

	wmove(ncu.textWin, 0, 0);
	wrefresh(ncu.textWin);
	while ((ch = getch()) != '\n')
	{
//		wprintw(ncu.textWin, "(%d)", ch);
		// Backspace
		if (ch == KEY_BACKSPACE) {
			if (j > 0) {
				wmove(ncu.textWin, 0, --j);
				wdelch(ncu.textWin);
				strncpy(clients[i].rd + j, clients[i].rd + j + 1, len - j);
				len--;
				wrefresh(ncu.textWin);
			}
		}
		else if (ch == KEY_DC) {
			if (j < len) {
				wdelch(ncu.textWin);
				strncpy(clients[i].rd + j, clients[i].rd + j + 1, len - j);
				len--;
				wrefresh(ncu.textWin);
			}
		}
		else if (ch == KEY_LEFT) {
			if (j > 0) {
				wmove(ncu.textWin, 0, --j);
				wrefresh(ncu.textWin);
			}
		}
		else if (ch == KEY_RIGHT) {
			if (j < len) {
				wmove(ncu.textWin, 0, ++j);
				wrefresh(ncu.textWin);
			}
		}
		else if (ch != ERR && ch >= 32 && ch <= 126) {
			if (j < BUF_CLIENTS - 1) {
				if (j < len) {
					strncpy(clients[i].rd + j + 1, clients[i].rd + j, len - j);
					winsch(ncu.textWin, ch);
					wmove(ncu.textWin, 0, j + 1);
				}
				else {
					wprintw(ncu.textWin, "%c", ch);
				}
				clients[i].rd[j++] = ch;
				len++;
				wrefresh(ncu.textWin);
			}
			else {
				clients[i].rd[--j] = '\0';
				clients[i].rd[j - 1] = ch;
				wprintw(ncu.textWin, "\b%c", ch);
				wrefresh(ncu.textWin);
			}
		}
	}
	clients[i].rd[len] = '\0';
	strcpy(clients[i].wr, clients[i].rd);
	wclear(ncu.textWin);
	wrefresh(ncu.textWin);
}

static void				read_clients(int i)
{
	int					ret;

	ret = read(clients[i].fd, clients[i].rd, BUF_CLIENTS - 1);
	if (ret <= 0) {
		clients[i].leaved = 1;
		return;
	}
	clients[i].rd[ret] = '\0';
	if (!clients[i].user[0]) {
		char *ptr = strstr(clients[i].rd, "/USER ");
		if (ptr && *(ptr + 6)) {
			strcpy(clients[i].user, "[");
			strncpy(clients[i].user + 1, ptr + 6, 8);
			strcat(clients[i].user, "] ");
			strcpy(clients[i].wr, clients[i].user);
			strcat(clients[i].wr, "\e[32mconnected\e[0m\n");
		} else {
			clients[i].try--;
		}
	} else {
		strncpy(clients[i].wr, clients[i].rd, ret);
	}
}

static void				write_clients(int i, int size)
{
	char				*ptr;
	int					len;

	if (!clients[i].wr[0])
		return ;
	if (clients[i].fd == STDIN_FILENO)
		ptr = strjoin(clients[i].user, clients[i].wr);
	else
		ptr = clients[i].wr;
	len = strlen(ptr);
	for (int j = 0; j < size; j++) {
		if (clients[j].fd == -1)
			continue ;
		if (clients[j].fd == STDIN_FILENO) {
			wprintTime(ncu.tchatWin, time(NULL));
			wprintw(ncu.tchatWin, "%s\n", ptr);
		}
		else
			write(clients[j].fd, ptr, len);
	}
	if (clients[i].fd == STDIN_FILENO)
		free(ptr);
	memset(clients[i].wr, 0, BUF_CLIENTS);
}

static int 				check_clients(int size)
{
	for (int i = 0; i < size; i++) {
		if (clients[i].fd == -1)
			continue ;
		if (clients[i].leaved) {
			strcpy(clients[i].wr, clients[i].user);
			strcat(clients[i].wr, "\e[31mdisconnected\e[0m\n");
			write_clients(i, size);
			close(clients[i].fd);
			clear_clients(&clients[i], 1);
		}
		else if (!clients[i].user[0] && clients[i].try <= 0) {
			write(clients[i].fd, "Nickname not defined.\n", 22);
			close(clients[i].fd);
			clear_clients(&clients[i], 1);
		}
	}
	return (clients[0].fd != -1);
}

void					loop(int server, int size)
{
	fd_set				fdr;
	fd_set				fdw;
	int					max;

	while (check_clients(size))
	{
		wrefresh(ncu.tchatWin);
		wcursyncup(ncu.textWin);
		wrefresh(ncu.textWin);
		max = init_select(server, size, &fdr, &fdw);
		if (select(max + 1, &fdr, &fdw, NULL, NULL) == -1)
			break;
		if (server && FD_ISSET(server, &fdr))
			accept_connection(server);
		for (int i = 0; i < size; i++) {
			if (clients[i].fd == -1)
				continue ;
			if (FD_ISSET(clients[i].fd, &fdr)) {
				if (clients[i].fd == STDIN_FILENO)
					read_in(i);
				else
					read_clients(i);
			}
			if (FD_ISSET(clients[i].fd, &fdw))
				write_clients(i, size);
		}
	}
	for (int i = 0; i < size; i++) {
		if (clients[i].fd != -1)
			close(clients[i].fd);
	}
	if (server)
		close(server);
	ncurses_end();
}
