/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/21 15:24:21 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/03/27 13:08:50 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "options.h"

t_options		*nmap_options(int getsize)
{
	static t_options	options[] = {
		{ "-t", "--timeout", "value", "[2000 default] Wait time for host answer (in ms)", get_timeout_parameters },
		{ "-S", "--scan", "type", SUPPORTED_SCANS, get_scans_parameters },
		{ "-s", "--speedup", "rate", "[250 max] Number of parallel threads to use", get_threads_parameters },
		{ "-p", "--ports", "range", "[1024 max] Ports to scan (eg: 1-10 or 1,2,3 or 1,5-15)", get_ports_parameters },
		{ "-f", "--file", "filename", "File name containing IP addresses to scan", get_file_parameters },
		{ "-i", "--ip", "address", "Ip address to scan in dot format", get_ip_parameters },
		{ "-h", "--help", (char *)0, "Print this help screen and return", print_help },
/*
		{ 'd', "deep", "Scans all addresses from a given host" },
		{ '', "src", "Spoof the src address" },
		{ 'o', "osscan", "Scan the host single threaded for guessing the OS" },
		{ 'c', "closed", "Show closed ports too on display" },
*/
	};

	if (getsize)
		return (t_options *)(sizeof(options) / sizeof(options[0]));
	return (options);
}

t_scans			*nmap_scans(int getsize)
{
	static t_scans		scans[] = {
		{ "SYN", ( 1 << 0) },
		{ "NULL", ( 1 << 1) },
		{ "FIN", ( 1 << 2) },
		{ "XMAS", ( 1 << 3) },
		{ "ACK", ( 1 << 4) },
		{ "UDP", ( 1 << 5) },
	};

	if (getsize)
		return (t_scans *)(sizeof(scans) / sizeof(scans[0]));
	return (scans);
}