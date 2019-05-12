/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 00:24:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/07 00:38:07 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTE_REMOVAL_H
# define QUOTE_REMOVAL_H

typedef struct	s_quote_removal
{
	char		value;
	void		(*handler)(char *, char *, size_t *);
}				t_q_removal;

#endif
