/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 07:01:52 by frmarinh          #+#    #+#             */
/*   Updated: 2017/09/25 21:12:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"
#include <stdio.h>

static void		print_char(int i, char c)
{
	while (i--)
		printf("%c", c);
}

static bool		check_if_open(t_queue *head)
{
	t_queue		*tail	= head;
	bool		is_open	= false;

	while (is_open == false && tail && tail->port == head->port)
	{
		is_open = tail->open && tail->filtered == false;
		tail = tail->next;
	}
	return (is_open);
}

static int		count_scan_type()
{
	t_scan_type		*scans	= globals->nmap->scans;
	int 			i		= 0;
	while (scans)
	{
		i++;
		scans = scans->next;
	}
	return i;
}

static char		*ft_dstrjoin(char *s1, char *s2, short flag)
{
	char	*result;
	char	*tmp;
	char	*pt1;
	char	*pt2;

	result = NULL;
	if (s1 == NULL)
		s1 = ft_strnew(0);
	pt1 = s1;
	pt2 = s2;
	if (s1 && (result = ft_strnew(
		(ft_strlen(s1) + (s2 != NULL ? ft_strlen(s2) : 0) + 1000))))
	{
		tmp = result;
		while (*s1)
			*tmp++ = *s1++;
		while (s2 && *s2)
			*tmp++ = *s2++;
		*tmp = '\0';
	}
	if ((flag == 1 && pt1) || (flag == 3 && pt1))
		ft_strdel(&pt1);
	if ((flag == 2 && pt2) || (flag == 3 && pt2))
		ft_strdel(&pt2);
	return (result);
}

static void		display_ports(t_queue *queues, char *text)
{
	t_queue		*ptr		= NULL;
	char		*proto		= NULL;
	int			scan_types	= 0;
	int			opcl		= 0;
	int			filtered	= 0;

	print_char(45, '_');
	printf(text);
	print_char(45, '_');
	printf("\n");
	printf("PORT\tSERVICE\t\tSCAN TYPE(STATUS)");
	int count = count_scan_type();
	print_char(count * 1.5, '\t');
	printf("HOST\n");
	while (queues)
	{
		ptr = NULL;
		printf("%d", queues->port);
		print_char(1, '\t');
		printf("%-10s", queues->service);
		print_char(1, '\t');

		ptr = queues;
		scan_types = 0;
		opcl = 0;
		while (ptr && ptr->port == queues->port && !ft_strcmp(ptr->host, queues->host)) {
			if (!ft_strcmp(ptr->scan, "SYN")) {
				scan_types |= 0x0001;
				if (ptr->filtered)
					filtered |= 0x0001;
				else if (ptr->open)
					opcl |= 0x0001;
			}
			else if (!ft_strcmp(ptr->scan, "NULL")) {
				scan_types |= 0x0002;
				if (ptr->filtered)
					filtered |= 0x0002;
				else if (ptr->open)
					opcl |= 0x0002;
			}
			else if (!ft_strcmp(ptr->scan, "FIN")) {
				scan_types |= 0x0004;
				if (ptr->filtered)
					filtered |= 0x0004;
				else if (ptr->open)
					opcl |= 0x0004;
			}
			else if (!ft_strcmp(ptr->scan, "XMAS")) {
				scan_types |= 0x0008;
				if (ptr->filtered)
					filtered |= 0x0008;
				else if (ptr->open)
					opcl |= 0x0008;
			}
			else if (!ft_strcmp(ptr->scan, "ACK")) {
				scan_types |= 0x0010;
				if (ptr->filtered)
					filtered |= 0x0010;
				else if (ptr->open)
					opcl |= 0x0010;
			}
			else if (!ft_strcmp(ptr->scan, "UDP")) {
				scan_types |= 0x0020;
				if (ptr->filtered)
					filtered |= 0x0020;
				else if (ptr->open)
					opcl |= 0x0020;
			}
			ptr = ptr->next;
		}

		int			i = 0;
		char		*to_print	= ft_strnew(0);
		char		*tmp		= ft_strnew(0);
		if (scan_types & 0x0001) {
			asprintf(&tmp, ((i == 0) ? "%s" : " %s"), "SYN");
			to_print = ft_dstrjoin(to_print, tmp, 2);

			asprintf(&tmp, "(%s)", (opcl & 0x0001 ? "Open" : (filtered & 0x0001 ? "Filtered" : "Closed"))); i++;
			to_print = ft_dstrjoin(to_print, tmp, 2);
		}
		if (scan_types & 0x0002) {
			asprintf(&tmp, ((i == 0) ? "%s" : " %s"), "NULL");
			to_print = ft_dstrjoin(to_print, tmp, 2);

			asprintf(&tmp, "(%s)", ((opcl & 0x0002) ? "Open" : (filtered & 0x0002 ? "Filtered" : "Closed"))); i++;
			to_print = ft_dstrjoin(to_print, tmp, 2);
		}
		if (scan_types & 0x0004) {
			asprintf(&tmp, ((i == 0) ? "%s" : " %s"), "FIN");
			to_print = ft_dstrjoin(to_print, tmp, 2);

			asprintf(&tmp, "(%s)", ((opcl & 0x0004) ? "Open" : (filtered & 0x0004 ? "Filtered" : "Closed"))); i++;
			to_print = ft_dstrjoin(to_print, tmp, 2);
		}
		if (scan_types & 0x0008) {
			asprintf(&tmp, ((i == 0) ? "%s" : " %s"), "XMAS");
			to_print = ft_dstrjoin(to_print, tmp, 2);

			asprintf(&tmp, "(%s)", ((opcl & 0x0008) ? "Open" : (filtered & 0x0008 ? "Filtered" : "Closed"))); i++;
			to_print = ft_dstrjoin(to_print, tmp, 2);
		}
		if (scan_types & 0x0010) {
			asprintf(&tmp, ((i == 0) ? "%s" : " %s"), "ACK");
			to_print = ft_dstrjoin(to_print, tmp, 2);
			asprintf(&tmp, "(%s)", ((opcl & 0x0010) ? "Filtered" : "Unfiltered")); i++;
			to_print = ft_dstrjoin(to_print, tmp, 2);
		}
		if (scan_types & 0x0020) {
			asprintf(&tmp, ((i == 0) ? "%s" : " %s"), "UDP");
			to_print = ft_dstrjoin(to_print, tmp, 2);

			asprintf(&tmp, "(%s)", ((opcl & 0x0020) ? "Open" : (filtered & 0x0020 ? "Filtered" : "Closed"))); i++;
			to_print = ft_dstrjoin(to_print, tmp, 2);
		}

		printf("%-*s", ft_strlen(to_print) + 5, to_print);
		printf("%s\n", queues->host);
		queues = ptr;
	}
}

static void		parse_not_done(t_queue *queues)
{
	while (queues)
	{
		if (!queues->done) {
			if (!ft_strcmp(queues->scan, "SYN")) {
				queues->open = false;
				queues->filtered = true;
			}
			else if (!ft_strcmp(queues->scan, "ACK")) {
				queues->open = false;
				queues->filtered = true;
			}
			else { // other type are all opened when there is no answer (at least we think)
				queues->open = true;
			}
		}
		queues = queues->next;
	}
}

static t_queue	*sort_by_port(t_queue *head)
{
	t_queue		*tail;
	t_queue		*next;
	t_queue		*ptr;

	tail = head;
	while (tail)
	{
		next = tail->next;
		if (next && next->port < tail->port)
		{
			if (next->port < head->port) {
				tail->next = next->next;
				next->next = head;
				head = next;
			} else {
				ptr = head;
				while (ptr->next && ptr != next) {
					if (next->port < ptr->next->port) {
						tail->next = next->next;
						next->next = ptr->next;
						ptr->next = next;
						break ;
					}
					ptr = ptr->next;
				}
			}
		}
		else
			tail = tail->next;
	}
	return head;
}

static void		sort_open_close(t_queue *head, t_queue **open, t_queue **close)
{
	t_queue		*tail = head;
	t_queue		*ptr;
	bool		is_open = false;

	while (head)
	{
		is_open = head->open && !head->filtered;
		tail = head;
		while (tail->next && tail->next->port == head->port)
		{
			if (!is_open)
				is_open = tail->next->open && !tail->next->filtered;
			tail = tail->next;
		}
		ptr = tail->next;
		if (is_open)
		{
			tail->next = *open;
			*open = head;
		}
		else
		{
			tail->next = *close;
			*close = head;
		}
		head = ptr;
	}
}

static t_queue	*sort_by_address(t_queue *queue)
{
	t_queue		*tail	= queue;
	t_queue		*end	= NULL;
	t_queue		*head	= NULL;
	t_queue		*save	= NULL;
	t_queue		*ptr	= NULL;

	while (tail && tail->next)
	{
		end = tail;
		while (end->next && end->next->port == tail->port)
			end = end->next;
		if (end != tail) {
			head = tail;
			while (head->next != end->next && !ft_strcmp(head->next->host, tail->host))
				head = head->next;
			ptr = head;
			while (ptr->next != end->next)
			{
				if (!ft_strcmp(ptr->next->host, tail->host))
				{
					save = ptr->next;
					ptr->next = save->next;
					save->next = head->next;
					head->next = save;
					head = save;
				}
				else
					ptr = ptr->next;
			}
			tail = head;
		}
		tail = tail->next;
	}
	return (queue);
}

void		display_handler()
{
	t_queue		*queues		= globals->all_queues;
	t_queue		*open_q		= NULL;
	t_queue		*close_q	= NULL;
	t_flag		*closed		= get_flag("closed");
	float		ms_time		= 0;

	queues = sort_by_port(queues);
	queues = sort_by_address(queues);
	parse_not_done(queues);
	sort_open_close(queues, &open_q, &close_q);
	if (open_q) {
		display_ports(open_q, "OPENED_PORTS");
		printf("\n");
	}
	if (close_q && closed)
		display_ports(close_q, "CLOSED_PORTS");
	ms_time = ((globals->end_time.tv_sec - globals->start_time.tv_sec) * 1000000 + globals->end_time.tv_usec) - globals->start_time.tv_usec;
	float time_value = ms_time / 1000;
	printf ("Execution time: %.3fms\n", time_value);
	free_datas(globals->nmap);
	exit(0);
}

void		init_display(t_nmap *nmap)
{
	struct sigaction act;

	gettimeofday (&globals->end_time, NULL);
	globals->nmap = nmap;
	ft_memset (&act, 0, sizeof(struct sigaction));
	act.sa_sigaction = &display_handler;
	act.sa_flags = SA_SIGINFO;
	if (sigaction(SIGALRM, &act, NULL) < 0) {
		return ;
	}
	alarm(EXECUTION_TIME);
}
