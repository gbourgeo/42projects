/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_intern.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 16:24:36 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/11 17:38:39 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_INTERN_H
# define SIGNAL_INTERN_H

int		signal_to_default(void);
int		sig_to_pgid(int pgid);

char	*sig_err_translate(int sig);

#endif
