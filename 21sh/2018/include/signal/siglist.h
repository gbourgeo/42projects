/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   siglist.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 17:21:48 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/28 17:29:51 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGLIST_H
# define SIGLIST_H

# include <signal.h>

# define SGHUP		"hangup"
# define SINT		"interrupt"
# define SQUIT		"quit"
# define SILL		"illegal instruction"
# define STRAP		"BPT trace/trap"
# define SABRT		"ABORT trap"
# define SEMT		"EMT trap"
# define SFPE		"Floating point exception"
# define SKILL		"Killed"
# define SBUS		"Bus error"
# define SSEGV		"Segmentation fault"
# define SSYS		"Bad system call"
# define SPIPE		"Broken pipe"
# define SALRM		"Alarm clock"
# define STERM		"Terminated"
# define SURG		"Urgent IO condition"
# define SSTOP		"Stopped"
# define STSTP		"Stopped"
# define SCONT		"Continue"
# define SCHLD		"Child death or stop"
# define STTIN		"Stopped"
# define STTOU		"Stopped"
# define SIO		"I/O ready"
# define SXCPU		"Cputime limit exceeded"
# define SXFSZ		"File limit"
# define SVTALRM	"Virtual timer expired"
# define SPROF		"Profiling timer expired"
# define SWINCH		"Window changed"
# define SLOST		"Record lock"
# define SUSR1		"User defined signal 1"
# define SUSR2		"User defined signal 2"

#endif
