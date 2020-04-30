/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/21 15:24:21 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/04/30 12:02:05 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "options.h"

t_options		*nmap_options(int getsize)
{
	static t_options	options[] = {
		{ "-v", "--verbose", (char *)0, "Verbose mode", get_verbose_parameters },
		{ "-t", "--timeout", "value", "[1000 default] Wait time for host answer in milliseconds.\n"
		"\t\tSpecify the seconds, minutes or hours by adding s, m or h at the end (eg. 10s, 1m, 1h)", get_timeout_parameters },
		{ "-S", "--scan", "type", SUPPORTED_SCANS, get_scans_parameters },
		{ "-s", "--speedup", "rate", "[250 max] Number of parallel threads to use", get_threads_parameters },
		{ "-r", "--retry", "number", "Number of retry to send packets", get_retry_parameters },
		{ "-p", "--ports", "range", "[1024 max] Ports to scan (eg: 1-10 or 1,2,3 or 1,5-15)", get_ports_parameters },
		{ "-if", "--iflist", (char *)0, "Print host interfaces and routes", get_iflist_parameters },
		{ "-i", "--ip", "address", "Ip address to scan in dot format", get_ip_parameters },
		{ "-h", "--help", (char *)0, "Print this help screen and return", get_help },
		{ "-f", "--file", "filename", "File name containing IP addresses to scan", get_file_parameters },
		{ "-e", "--interface", "name", "Specify the interface to use", get_interface_parameters },
		{ "-d", "--debug", (char *)0, "Debug mode", get_debug_parameters },
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