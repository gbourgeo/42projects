/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keylogger.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 05:57:11 by root              #+#    #+#             */
/*   Updated: 2019/08/06 00:56:49 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYLOGGER_H
# define KEYLOGGER_H

# include <linux/input.h>
# include <linux/keyboard.h>

int			get_keystate(int keybit, int socket);
int			shift_handler(int value, int state, int *modifier);
int			lock_handler(int value, int state, int *modifier, int *locker);

#endif
