/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_list.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 01:15:21 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/18 23:43:47 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERR_LIST_H
# define ERR_LIST_H

/*
** Errors list
*/
# define ERR_NOSUCHNICK	"401"
# define ERR_NOSUCHSERVER "402"
# define ERR_NOSUCHCHANNEL "403"
# define ERR_CANNOTSENDTOCHAN "404"
# define ERR_TOOMANYCHANNELS "405"
# define ERR_WASNOSUCHNICK "406"
# define ERR_TOOMANYTARGETS "407"
# define ERR_NOSUCHSERVICE "408"
# define ERR_NOORIGIN "409"
# define ERR_NORECIPIENT "411"
# define ERR_NOTEXTTOSEND "412"
# define ERR_NOTOPLEVEL "413"
# define ERR_WILDTOPLEVEL "414"
# define ERR_BADMASK "415"
# define ERR_UNKNOWNCOMMAND "421"
# define ERR_NOMOTD "422"
# define ERR_NOADMININFO "423"
# define ERR_FILEERROR "424"
# define ERR_NONICKNAMEGIVEN "431"
# define ERR_ERRONEUSNICKNAME "432"
# define ERR_NICKNAMEINUSE "433"
# define ERR_NICKCOLLISION "436"
# define ERR_UNAVAILABLERESOURCE "437"
# define ERR_USERNOTINCHANNEL "441"
# define ERR_NOTONCHANNEL "442"
# define ERR_USERONCHANNEL "443"
# define ERR_NOLOGIN "444"
# define ERR_SUMMONDISABLED "445"
# define ERR_USERDISABLED "446"
# define ERR_NOTREGISTERED "451"
# define ERR_NEEDMOREPARAMS "461"
# define ERR_ALREADYREGISTERED "462"
# define ERR_NOPERMFORHOST "463"
# define ERR_PASSWMISMATCH "464"
# define ERR_YOUREBANNEDCREEP "465"
# define ERR_YOUWILLBEBANNED "466"
# define ERR_KEYSET "467"
# define ERR_CHANNELISFULL "471"
# define ERR_UNKNOWNMODE "472"
# define ERR_INVITEONLYCHAN "473"
# define ERR_BANNEDFROMCHAN "474"
# define ERR_BADCHANNELKEY "475"
# define ERR_BADCHANMASK "476"
# define ERR_NOCHANMODES "477"
# define ERR_BANLISTFULL "478"
# define ERR_NOPRIVILEGES "481"
# define ERR_CHANOPRIVSNEEDED "482"
# define ERR_CANTKILLSERVER "483"
# define ERR_RESTRICTED "484"
# define ERR_UNIQOPPRIVSNEEDED "485"
# define ERR_NOOPERHOST "491"
# define ERR_UMODEUNKNOWNFLAG "501"
# define ERR_USERSDONTMATCH "502"

/*
** define for sv_err(..) function
*/
# define ER_0 { NULL, NULL, NULL },
# define ER_1 { NULL, NULL, ":No such nick" },
# define ER_2 { NULL, NULL, ":No such server" },
# define ER_3 { NULL, NULL, ":No such channel" },
# define ER_4 { NULL, NULL, ":Cannot send to channel" },
# define ER_5 { NULL, NULL, ":You have joined too many channels" },
# define ER_6 { NULL, NULL, ":There was no such nickname" },
# define ER_7 { NULL, NULL, ":Too many recipients. abort" },
# define ER_8 { NULL, NULL, ":No such service" },
# define ER_9 { NULL, NULL, ":No origin specified" },
# define ER_10 { NULL, NULL, NULL },
# define ER_11 { ":No recipient given (", NULL, ")" },
# define ER_12 { NULL, NULL, ":No text to send" }
# define ER_13 { NULL, NULL, ":No toplevel domain specified" },
# define ER_14 { NULL, NULL, ":Wildcard in toplevel domain" },
# define ER_15 { NULL, NULL, ":Bad Server/host mask" },
# define ER_16 { NULL, NULL, NULL }, { NULL, NULL, NULL }, { NULL, NULL, NULL },
# define ER_17 { NULL, NULL, NULL }, { NULL, NULL, NULL },
# define ER_18 { NULL, NULL, ":Unknown command" },
# define ER_19 { NULL, NULL, ":MOTD file is missing" },
# define ER_20 { NULL, NULL, ":No administrative info available" },
# define ER_21 { NULL, NULL, ":File error..." },
# define ER_22 { NULL, NULL, NULL }, { NULL, NULL, NULL }, { NULL, NULL, NULL }
# define ER_23 { NULL, NULL, NULL }, { NULL, NULL, NULL }, { NULL, NULL, NULL },
# define ER_24 { NULL, NULL, ":No nickname given" },
# define ER_25 { NULL, NULL, ":Erroneus nickname" },
# define ER_26 { NULL, NULL, ":Nickname is already in use" },
# define ER_27 { NULL, NULL, NULL }, { NULL, NULL, NULL },
# define ER_28 { NULL, NULL, ":Nickname collision" },
# define ER_29 { NULL, NULL, ":Nick/channel is temporarily unavailable" },
# define ER_30 { NULL, NULL, NULL }, { NULL, NULL, NULL }, { NULL, NULL, NULL },
# define ER_31 { NULL, NULL, ":They aren't on that channel" },
# define ER_32 { NULL, NULL, ":You're not on that channel" }
# define ER_33 { NULL, NULL, ":is already on channel" },
# define ER_34 { NULL, NULL, ":User not logged in" },
# define ER_35 { NULL, NULL, ":SUMMON has been disabled" },
# define ER_36 { NULL, NULL, ":USERS has been disbled" },
# define ER_37 { NULL, NULL, NULL }, { NULL, NULL, NULL }, { NULL, NULL, NULL },
# define ER_38 { NULL, NULL, NULL },
# define ER_39 { NULL, NULL, ":You have not registered" },
# define ER_40 { NULL, NULL, NULL }, { NULL, NULL, NULL }, { NULL, NULL, NULL },
# define ER_41 { NULL, NULL, NULL }, { NULL, NULL, NULL }, { NULL, NULL, NULL },
# define ER_42 { NULL, NULL, NULL }, { NULL, NULL, NULL }, { NULL, NULL, NULL }
# define ER_43 { NULL, NULL, ":Not enough parameters" },
# define ER_44 { NULL, NULL, ":Unauthorized command (already registered)" },
# define ER_45 { NULL, NULL, ":Your host isn't among the privileged" },
# define ER_46 { NULL, NULL, ":Password incorrect" },
# define ER_47 { NULL, NULL, ":You are banned from this server" },
# define ER_48 { NULL, NULL, ":You will be banned soon" },
# define ER_49 { NULL, NULL, ":Channel key already set" },
# define ER_50 { NULL, NULL, NULL }, { NULL, NULL, NULL }, { NULL, NULL, NULL },
# define ER_51 { NULL, NULL, ":Cannot join channel (+1)" },
# define ER_52 { NULL, ":is unknown mode char to me for", NULL }
# define ER_53 { NULL, NULL, ":Cannot join channel (+i)" },
# define ER_54 { NULL, NULL, ":Cannot join channel (+b)" },
# define ER_55 { NULL, NULL, ":Cannot join channel (+k)" },
# define ER_56 { NULL, NULL, ":Bad channel mask" },
# define ER_57 { NULL, NULL, ":Channel doesn't support modes" },
# define ER_58 { NULL, NULL, ":Channel list is full" },
# define ER_59 { NULL, NULL, NULL }, { NULL, NULL, NULL },
# define ER_60 { NULL, NULL, ":Permission Denied- You're not an IRC operator" },
# define ER_61 { NULL, NULL, ":You're not channel operator" },
# define ER_62 { NULL, NULL, ":You can't kill a server!" }
# define ER_63 { NULL, NULL, ":Your connection is restricted!" },
# define ER_64 { NULL, NULL, ":You're not the original channel operator" },
# define ER_65 { NULL, NULL, NULL }, { NULL, NULL, NULL }, { NULL, NULL, NULL },
# define ER_66 { NULL, NULL, NULL }, { NULL, NULL, NULL },
# define ER_67 { NULL, NULL, ":No O-lines for your host" },
# define ER_68 { NULL, NULL, NULL }, { NULL, NULL, NULL }, { NULL, NULL, NULL },
# define ER_69 { NULL, NULL, NULL }, { NULL, NULL, NULL }, { NULL, NULL, NULL },
# define ER_70 { NULL, NULL, NULL }, { NULL, NULL, NULL }, { NULL, NULL, NULL },
# define ER_71 { NULL, NULL, ":Unknown MODE flag" },
# define ER_72 { NULL, NULL, ":Cannot change mode for other users" }

# define ER_ALL1 ER_1 ER_2 ER_3 ER_4 ER_5 ER_6 ER_7 ER_8 ER_9 ER_10 ER_11 ER_12
# define ER_ALL2 ER_13 ER_14 ER_15 ER_16 ER_17 ER_18 ER_19 ER_20 ER_21 ER_22
# define ER_ALL3 ER_23 ER_24 ER_25 ER_26 ER_27 ER_28 ER_29 ER_30 ER_31 ER_32
# define ER_ALL4 ER_33 ER_34 ER_35 ER_36 ER_37 ER_38 ER_39 ER_40 ER_41 ER_42
# define ER_ALL5 ER_43 ER_44 ER_45 ER_46 ER_47 ER_48 ER_49 ER_50 ER_51 ER_52
# define ER_ALL6 ER_53 ER_54 ER_55 ER_56 ER_57 ER_58 ER_59 ER_60 ER_61 ER_62
# define ER_ALL7 ER_63 ER_64 ER_65 ER_66 ER_67 ER_68 ER_69 ER_70 ER_71 ER_72

#endif
