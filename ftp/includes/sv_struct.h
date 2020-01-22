/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:29:39 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/21 15:32:49 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SV_STRUCT_H
# define SV_STRUCT_H


typedef struct	s_response_options
{
	char		value;
	int			(*fct)();
}				t_ropt;

t_ropt			*sv_response_opt(char c);

# endif
