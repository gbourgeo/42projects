/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_err.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 22:55:47 by root              #+#    #+#             */
/*   Updated: 2017/03/28 23:03:57 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERR_H
# define FT_ERR_H

# define ERR_1		{ "Echo Reply", NULL }
# define ERR_2		{ "", NULL }
# define ERR_3		{ "", NULL }
# define ERR_4		{ "Destination Net Unreachable", "Destination Host Unreachable"
# define ERR_5			"Destination Protocol Unreachable"
# define ERR_6			"Destination Port Unreachable"
# define ERR_7			"frag needed and DF set", "Source Route Failed"
# define ERR_8			"Destination Net Unknown", "Destination Host Unknown"
# define ERR_9			"Source Host Isolated", "Destination Net Prohibited"
# define ERR_10			"Destination Host Prohibited"
# define ERR_11			"Destination Net Unreachable for Type of Service"
# define ERR_12			"Destination Host Unreachable for Type of Service"
# define ERR_13			"Packet filtered", "Precedence Violation"
# define ERR_14			"Precedence Cutoff", NULL }
# define ERR_15		{ "Source Quench", NULL }
# define ERR_16		{ "Redirect Network", "Redirect Host"
# define ERR_17			"Redirect Type of Service and Network"
# define ERR_18			"Redirect Type of Service and Host", NULL }
# define ERR_19		{ "", NULL }
# define ERR_20		{ "", NULL }
# define ERR_21		{ "Echo Request", NULL }
# define ERR_22		{ "", NULL }
# define ERR_23		{ "", NULL }
# define ERR_24		{"Time to live exceeded", "Frag Reassembly time exceeded", NULL}
# define ERR_25		{ "Parameter problem: pointer = %u", NULL }
# define ERR_26		{ "Timestamp", NULL }
# define ERR_27		{ "Timestamp Reply", NULL }
# define ERR_28		{ "Information Request", NULL }
# define ERR_29		{ "Information Reply", NULL }
# define ERR_30		{ "Address Mask Request", NULL }
# define ERR_31		{ "Address Mask Reply", NULL }
# define ERR_32		{ NULL }

# define ERRLIST_1 ERR_1, ERR_2, ERR_3, ERR_4, ERR_5, ERR_6, ERR_7, ERR_8, ERR_9
# define ERRLIST_2 ERR_10, ERR_11, ERR_12, ERR_13, ERR_14, ERR_15, ERR_16, ERR_17
# define ERRLIST_3 ERR_18, ERR_19, ERR_20, ERR_21, ERR_22, ERR_23, ERR_24, ERR_25
# define ERRLIST_4 ERR_26, ERR_27, ERR_28, ERR_29, ERR_30, ERR_31, ERR_32

# define ERRLIST_FULL ERRLIST_1, ERRLIST_2, ERRLIST_3, ERRLIST_4

#endif
