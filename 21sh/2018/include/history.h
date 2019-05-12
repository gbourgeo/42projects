/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 05:31:13 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/29 13:39:37 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# include "struct.h"

# define TMP_PATH	"/tmp/.42sh_history"
# define HIST_NAME	".42sh_history"

void	create_hist(t_hist **begin, char **env);
void	save_history(t_line *line, char *buff, t_hist **curr, char **env);

#endif
