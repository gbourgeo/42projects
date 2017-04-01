/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 01:24:24 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/22 19:53:46 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

/*
** Here i regroup all commands the server will handle and their associated
** functions.
*/

# define AWAY		{ "AWAY", sv_away }
# define CONNECT	{ "CONNECT", sv_connect }
# define HELP		{ "HELP", sv_help }
# define JOIN		{ "JOIN", sv_join }
# define LEAVE		{ "LEAVE", sv_leave }
# define LIST		{ "LIST", sv_list }
# define MSG		{ "MSG", sv_msg }
# define MODE		{ "MODE", sv_mode }
# define NICK		{ "NICK", sv_nick }
# define PASS		{ "PASS", sv_pass }
# define QUIT		{ "QUIT", sv_quit }
# define USER		{ "USER", sv_user }
# define TOPIC		{ "TOPIC", sv_topic }
# define WHO		{ "WHO", sv_who }
# define END		{ NULL, NULL }

# define COMMANDS1 "AWAY", "CONNECT", "HELP", "JOIN", "LEAVE", "LIST", "MSG"
# define COMMANDS2 "MODE", "NICK", "PASS", "QUIT", "USER", "TOPIC", "WHO", NULL

# define SV_COMMANDS1 AWAY, CONNECT, HELP, JOIN, LEAVE, LIST, MSG, MODE, NICK
# define SV_COMMANDS2 PASS, QUIT, USER, TOPIC, WHO, END

#endif
