/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_source.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 21:18:49 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/16 20:29:15 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_SOURCE_H
# define BUILTIN_SOURCE_H

enum
{
	ERR_OK,
	ERR_IS_DIR,
	ERR_NOT_ARG,
	ERR_NO_SUCH_FILE,
	ERR_PERMISSION,
	ERR_MALLOC,
	ERR_NOT_FOUND,
};

#endif
