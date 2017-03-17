/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 01:14:30 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/17 01:23:33 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Here are the defined Messages displayed in help <command>
*/

# define SYNTAX1 "AWAY [<message>]", "CONNECT <_host_> [<port>]"
# define SYNTAX2 "HELP [<command>]", "JOIN <[#|&|+|!]channel> [key]"
# define SYNTAX3 "LEAVE <[#|&|+|!]channel>", "LIST [[#|&|+|!]channel]"
# define SYNTAX4 "MSG <nick> <message>", "NICK <nick>", "PASS <password>"
# define SYNTAX5 "QUIT [<comment>]", "USER <user> <mode> <unused> <realname>"
# define SYNTAX6 "TOPIC <[#|&|+|!]channel> [topic]", "WHO <channel|user>", NULL

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
# define NICK_1 "When first connected to the IRC server, NICK is required to"
# define NICK_2 "set the client's nickname."
# define NICK_3 "NICK will also change the client's nickname once a connection"
# define NICK_4 "has been established."
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
# define SV_HELP8 { NICK_1, NICK_2, NICK_3, NICK_4, NULL }
# define SV_HELP9 { PASS_1, PASS_2, NULL }
# define SV_HELP10 { QUIT_1, QUIT_2, QUIT_3, NULL}
# define SV_HELP11 { USER_1, USER_2, USER_3, USER_4, USER_5, NULL}
# define SV_HELP12 { TOPIC_1, TOPIC_2, TOPIC_3, TOPIC_4, TOPIC_5, NULL }
# define SV_HELP13 { W1, W2, W3, W4, W5, W6, W7, W8, W9, W10, NULL}

# define HELP1 SV_HELP1, SV_HELP2, SV_HELP3, SV_HELP4, SV_HELP5, SV_HELP6
# define HELP2 SV_HELP7, SV_HELP8, SV_HELP9, SV_HELP10, SV_HELP11
# define HELP3 SV_HELP12, SV_HELP13
