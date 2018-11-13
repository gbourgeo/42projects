/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keylogger.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 05:57:11 by root              #+#    #+#             */
/*   Updated: 2018/10/31 18:37:48 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYLOGGER_H
# define KEYLOGGER_H

#include <linux/input.h>
#include <linux/keyboard.h>

int			get_keystate(int keybit);
int			shift_handler(int value, int state, int *modifier);
int			lock_handler(int value, int state, int *modifier, int *locker);

#endif
