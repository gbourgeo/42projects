/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_error.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 04:08:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/15 02:24:21 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_ERROR_H
# define TOKEN_ERROR_H

enum
{
	ERR_FREE_ALL = -1,
	ERR_NONE = 0,
	ERR_MALLOC,
	ERR_EOF,
	ERR_ALIAS
};

#endif
