/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 06:33:27 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/10/31 09:32:39 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

struct s_cl		clients[MAX_CLIENTS];
extern t_ncu	ncu;

static void			infoLine(char *ip, char *port)
{
	wclear(ncu.infoLine);
	wrefresh(ncu.infoLine);
	wprintTime(ncu.infoLine, time(NULL));
	wattron(ncu.infoLine, COLOR_PAIR(1));
	wprintw(ncu.infoLine, "Connected to ");
	wattroff(ncu.infoLine, COLOR_PAIR(1));
	wattron(ncu.infoLine, COLOR_PAIR(3));
	wprintw(ncu.infoLine, "%s", ip);
	wattroff(ncu.infoLine, COLOR_PAIR(3));
	wattron(ncu.infoLine, COLOR_PAIR(1));
	wprintw(ncu.infoLine, ":");
	wattroff(ncu.infoLine, COLOR_PAIR(1));
	wattron(ncu.infoLine, COLOR_PAIR(3));
	wprintw(ncu.infoLine, "%s", port);
	wattroff(ncu.infoLine, COLOR_PAIR(3));
	wrefresh(ncu.infoLine);
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
		if (clients[i].fd == 0 || clients[i].leaved)
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
		if (clients[i].fd)
			continue ;
		clear_clients(&clients[i], 1);
		clients[i].fd = fd;
		clients[i].try = 1;
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
	strcpy(clients[i].wr, "[");
	strcat(clients[i].wr, clients[i].user);
	strcat(clients[i].wr, "] ");
	strcat(clients[i].wr, clients[i].rd);
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
	if (clients[i].try == 1) {
		if (!strncmp(clients[i].rd, "/NICK ", 6))
			strncpy(clients[i].user, clients[i].rd + 6, NICK_CLIENTS);
		clients[i].try = 0;
	}
	else if (!strncmp(clients[i].rd, "/USERS ", 7))
		parse_users(clients[i].rd, 7);
	strcpy(clients[i].wr, clients[i].rd);
	clients[i].rd[0] = '\0';
}

static void				write_clients(int i, int size)
{
	int					len;

	len = strlen(clients[i].wr);
	for (int j = 0; j < size; j++) {
		if (clients[j].fd == 0 || clients[j].leaved)
			continue ;
		if (clients[j].fd == STDOUT_FILENO) {
			if (*clients[j].wr != '/') {
				wprintTime(ncu.tchatWin, time(NULL));
				wprintw(ncu.tchatWin, "%s\n", clients[i].wr);
			}
		}
		else if (j != i)
			write(clients[j].fd, clients[i].wr, len);
	}
	clients[i].wr[0] = '\0';
}

static int 				check_clients(int server)
{
	if (!server)
		return (clients[1].leaved == 0);
	for (int i = 0; i < MAX_CLIENTS; i++) {
		if (clients[i].fd == 0)
			continue ;
		if (clients[i].leaved) {
			del_user(clients[i].user);
			send_users("/USERS ", clients);
			sprintf(clients[i].wr, "[%s] disconnected.", clients[i].user);
			write_clients(i, MAX_CLIENTS);
			close(clients[i].fd);
			clear_clients(&clients[i], 1);
		}
		else if (!clients[i].try) {
			if (!clients[i].user[0]) {
				write(clients[i].fd, "Kicked from server (Invalid username)\n", 38);
				close(clients[i].fd);
				clear_clients(&clients[i], 1);
			} else {
				add_user(clients[i].user);
				send_users("/USERS ", clients);
				sprintf(clients[i].wr, "[%s] connected.", clients[i].user);
				write_clients(i, MAX_CLIENTS);
				clients[i].try = 2;
			}
		}
	}
	return (clients[0].leaved == 0);
}

void					loop(int server, int size, char *ip, char *port)
{
	fd_set				fdr;
	fd_set				fdw;
	int					max;

	ncurses_start();
	infoLine(ip, port);
	while (check_clients(server))
	{
		wrefresh(ncu.tchatWin);
		aff_users(&ncu);
		wcursyncup(ncu.textWin);
		wrefresh(ncu.textWin);
		max = init_select(server, size, &fdr, &fdw);
		if (select(max + 1, &fdr, &fdw, NULL, NULL) == -1)
			break;
		if (server && FD_ISSET(server, &fdr))
			accept_connection(server);
		for (int i = 0; i < size; i++) {
			if (clients[i].fd == 0)
				continue ;
			if (FD_ISSET(clients[i].fd, &fdr)) {
				if (clients[i].fd == STDOUT_FILENO)
					read_in(i);
				else
					read_clients(i);
			}
			if (FD_ISSET(clients[i].fd, &fdw))
				write_clients(i, size);
		}
	}
	ncurses_end();
	for (int i = 0; i < size; i++) {
		if (clients[i].fd && clients[i].fd != STDOUT_FILENO)
			close(clients[i].fd);
	}
	clear_clients(clients, MAX_CLIENTS);
	if (server)
		close(server);
	clear_users();
	printf("Disconnected from the server.\n");
}
