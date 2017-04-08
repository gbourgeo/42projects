/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 01:27:53 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/08 05:09:38 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLAGS_H
# define FLAGS_H

/*
** The various modes available for channels are as follows:
**
**        O - give "channel creator" status;
**        o - give/take channel operator privilege;
**        v - give/take the voice privilege;
**
**        a - toggle the anonymous channel flag;
**        i - toggle the invite-only channel flag;
**        m - toggle the moderated channel;
**        n - toggle the no messages to channel from clients on the
**            outside;
**        q - toggle the quiet channel flag;
**        p - toggle the private channel flag;
**        s - toggle the secret channel flag;
**        r - toggle the server reop channel flag;
**        t - toggle the topic settable by channel operator only flag;
**
**        k - set/remove the channel key (password);
**        l - set/remove the user limit to channel;
**
**        b - set/remove ban mask to keep users out;
**        e - set/remove an exception mask to override a ban mask;
**        I - set/remove an invitation mask to automatically override
**            the invite-only flag;
*/

/*
** User flags.
*/
# define USER_MODES "aiwrOo"

# define USR_AWAY		0x0001
# define USR_INVISIBL	0x0002
# define USR_WALLOPS	0x0004
# define USR_RESTRICT	0x0008
# define USR_OP			0x0010
# define USR_LOCALOP	0x0020

# define US_MODS1 USR_AWAY, USR_INVISIBL, USR_WALLOPS, USR_RESTRICT, USR_OP
# define US_MODS2 USR_LOCALOP

/*
** Channel user flags && Channel flags.
*/
# define CHAN_MODES "Oovamnqpstkl"

# define CHFL_CREATOR	0x0001
# define CHFL_CHANOP	0x0002
# define CHFL_VOICE		0x0004

# define CHFL_ANON		0x0010
# define CHFL_MOD		0x0020
# define CHFL_NOMSG		0x0040
# define CHFL_QUIET		0x0080
# define CHFL_PRIV		0x0100
# define CHFL_SECRET	0x0200
# define CHFL_TOPIC		0x0400
# define CHFL_KEY		0x0800
# define CHFL_LIMIT		0x1000

# define CH_MODS1 CHFL_CREATOR, CHFL_CHANOP, CHFL_VOICE
# define CH_MODS2 CHFL_ANON, CHFL_MOD, CHFL_NOMSG, CHFL_QUIET
# define CH_MODS3 CHFL_PRIV, CHFL_SECRET, CHFL_TOPIC, CHFL_KEY, CHFL_LIMIT

#endif
