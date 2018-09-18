/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 01:14:30 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/18 15:03:29 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELP_H
# define HELP_H

/*
** Here are the defined Messages displayed in help <command>
*/
# define SYN1 "AWAY [<message>]"
# define SYN2 "CONNECT <_host_> [<port>]"
# define SYN3 "HELP [<command>]"
# define SYN4 "JOIN <[#|&|+|!]channel> [key]"
# define SYN5 "LEAVE <[#|&|+|!]channel>"
# define SYN6 "LIST [[#|&|+|!]channel]"
# define SYN7 "MSG <nick> <message>"
# define SYN8 "MODE <nick> <+/-> <mode>, MODE <channel> <+|-> <modes>"
# define SYN9 "NICK <nick>"
# define SYN10 "OPER <name> <password>"
# define SYN11 "PASS <password>"
# define SYN12 "QUIT [<comment>]"
# define SYN13 "USER <user> <mode> <unused> <realname>"
# define SYN14 "TOPIC <[#|&|+|!]channel> [topic]"
# define SYN15 "WHO <channel|user>"

# define SYNTAX1 SYN1, SYN2, SYN3, SYN4, SYN5, SYN6, SYN7, SYN8, SYN9
# define SYNTAX2 SYN10, SYN11, SYN12, SYN13, SYN14, SYN15

# define AWAY_1 "Without an argument, it will set you back.  With an argument,"
# define AWAY_2	"it will set you as AWAY with the specified message."
# define CONNECT_1 "Request the server to establish a connection to <host>."
# define CONNECT_2 "It is only available to FT_IRC Operators. ^^"
# define HELP_1 "HELP with a command name prints info about that command."
# define HELP_2 "HELP without parameters lists all IRC commands."
# define JOIN_1 "The JOIN command allows you to enter a public chat area."
# define JOIN_2 "Network wide channels are proceeded by a '#', while"
# define JOIN_3 "a local server channel is proceeded by an '&'. More than one"
# define JOIN_4 "channel may be specified, separated with commas (no spaces)."
# define LEAVE_1 "Requires at least a channel argument to be given. It will"
# define LEAVE_2 "exit the client from the specified channel. More than one"
# define LEAVE_3 "channel may be specified, separated with commas (no spaces)."
# define LIST_1 "Without any arguments, LIST will give an entire list of all"
# define LIST_2 "channels which are not set as secret (+s). The list will be in"
# define LIST_3 "the form: <#channel> <amount of users> :[topic]"
# define LIST_4 "If an argument supplied is a channel name, LIST will give just"
# define LIST_5 "the statistics for the given channel."
# define MSG_1 "MSG will send a message to the user or channel specified."
# define M_1 "MODE <nick> <+|-> <modes>"
# define M_2 "   USERMODE      DESCRIPTION"
# define M_3 "-----------------------------------------------------------------"
# define M_4 "      +O       - Designates this user is a local IRC operator"
# define M_5 "      +o       - Designates this user is an IRC operator"
# define M_6 "      +i       - Marks this users as invisible"
# define M_7 "      +r       - Designates the user has restricted connection"
# define M_8 ""
# define M_9 ""
# define M_10 "MODE <channel> <+|-> <modes>"
# define M_11 "  CHANNELMODE   DESCRIPTION"
# define M_12 "----------------------------------------------------------------"
# define M_13 "     +a       - Anonymous channel"
# define M_15 "     +m       - moderated channel"
# define M_16 "     +n       - No messages from client on the outside"
# define M_17 "     +q       - quiet channel"
# define M_18 "     +p       - Private channel"
# define M_19 "     +s       - Secret channel"
# define M_20 "     +t       - Topic settable by chanop only channel"
# define M_21 "     +k       - Set/remove channel key"
# define M_22 "     +l       - Set/remove user limit channel"

# define NICK_1 "When first connected to the IRC server, NICK is required to"
# define NICK_2 "set the client's nickname."
# define NICK_3 "NICK will also change the client's nickname once a connection"
# define NICK_4 "has been established."

# define OPER_1 "The OPER command requires two arguments to be given. The first"
# define OPER_2 "argument is the name of the operator as specified in the"
# define OPER_3 "configuration file. The second argument is the password for"
# define OPER_4 "the operator matching the name and host."
# define OPER_5 ""
# define OPER_6 "The operator privileges are shown on a successful OPER."

# define PASS_1 "PASS is used during registration to access"
# define PASS_2 "a password protected auth {} block."
# define QUIT_1 "Sends a message to the IRC server letting it know you would"
# define QUIT_2 "like to disconnect.  The quit message will be displayed to the"
# define QUIT_3 "users in the channels you were in when you are disconnected."
# define USER_1 "USER is used during registration to set your gecos"
# define USER_2 "and to set your username if the server cannot get"
# define USER_3 "a valid ident response.  The second and third fields"
# define USER_4 "are not used, but there must be something in them."
# define USER_5 "The reason is backwards compatibility"
# define TOPIC_1 "With only a channel argument, TOPIC shows the current topic"
# define TOPIC_2 "of the specified channel."
# define TOPIC_3 "With a second argument, it changes the topic on that channel"
# define TOPIC_4 "to [topic]. If the channel is +t, only chanops may change the"
# define TOPIC_5 "topic."

# define W1 "The WHO command displays information about a user,"
# define W2 "such as their GECOS information, their user@host,"
# define W3 "whether they are an IRC operator or not, etc."
# define W4 "The possible combinations for this field are listed here:"
# define W5 ""
# define W6 "H       -       The user is not away."
# define W7 "G       -       The user is set away."
# define W8 "*       -       The user is an IRC operator."
# define W9 "@       -       The user is a channel op in the channel listed."
# define W10 "+       -       The user is voiced in the channel listed."
# define SV_HELP1 { AWAY_1, AWAY_2, NULL }
# define SV_HELP2 { CONNECT_1, CONNECT_2, NULL }
# define SV_HELP3 { HELP_1, HELP_2, NULL }
# define SV_HELP4 { JOIN_1, JOIN_2, JOIN_3, JOIN_4, NULL }
# define SV_HELP5 { LEAVE_1, LEAVE_2, LEAVE_3, NULL }
# define SV_HELP6 { LIST_1, LIST_2, LIST_3, LIST_4, LIST_5, NULL }
# define SV_HELP7 { MSG_1, NULL }
# define SV_HELP8 { M_1, M_2, M_3, M_4, M_5, M_6, M_7, M_8, M_9, M_10, M_11
# define SV_HELP9 M_12, M_13, M_15, M_16, M_17, M_18, M_19, M_20, M_21
# define SV_HELP10 M_22, NULL }
# define SV_HELP11 { NICK_1, NICK_2, NICK_3, NICK_4, NULL }
# define SV_HELP12 { OPER_1, OPER_2, OPER_3, OPER_4, OPER_5, OPER_6, NULL }
# define SV_HELP13 { PASS_1, PASS_2, NULL }
# define SV_HELP14 { QUIT_1, QUIT_2, QUIT_3, NULL}
# define SV_HELP15 { USER_1, USER_2, USER_3, USER_4, USER_5, NULL}
# define SV_HELP16 { TOPIC_1, TOPIC_2, TOPIC_3, TOPIC_4, TOPIC_5, NULL }
# define SV_HELP17 { W1, W2, W3, W4, W5, W6, W7, W8, W9, W10, NULL}

# define HELP1 SV_HELP1, SV_HELP2, SV_HELP3, SV_HELP4, SV_HELP5, SV_HELP6
# define HELP2 SV_HELP7, SV_HELP8, SV_HELP9, SV_HELP10, SV_HELP11, SV_HELP12
# define HELP3 SV_HELP13, SV_HELP14, SV_HELP15, SV_HELP16, SV_HELP17

#endif
