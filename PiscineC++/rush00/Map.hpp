/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 14:16:37 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/06/07 13:36:05 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
 #define MAP_HPP

# include <sys/time.h>
# include "Screen.hpp"
# include "GameBoard.hpp"
# include "PlayerHandler.hpp"

#define HEIGHT		40
#define WIDTH		60

typedef struct		s_map_border
{
	const char		*line;
	int				len;
}					t_border;

void				printBorder(Screen & screen);
void				printScore(Screen & screen, GameBoard & gameboard, PlayerHandler & players);

#endif
