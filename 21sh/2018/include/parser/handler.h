/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 01:53:57 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/16 18:44:17 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLER_H
# define HANDLER_H

# define H_LIST			{ parse_list }
# define H_AO_LIST		{ parse_ao_list }
# define H_PIPE			{ parse_pipe }
# define H_OPERATOR		{ parse_operator }
# define H_ASYNC		{ parse_async }
# define H_ARGUMENT		{ parse_argument }
# define H_IO_NUMBER	{ parse_io_number }
# define H_ERROR		{ parse_not_handled_yet }

#endif
