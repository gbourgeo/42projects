/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PlayerHandler.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 12:41:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/06/07 15:12:29 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYERHANDLER_HPP
# define PLAYERHANDLER_HPP

# include "Player.hpp"
# include "Screen.hpp"

typedef struct		s_player
{
	Player				*player;
	struct s_player		*prev;
	struct s_player		*next;
}					t_player;

class PlayerHandler
{
public:
	PlayerHandler();
	PlayerHandler(PlayerHandler const & src);
	~PlayerHandler();
	PlayerHandler & operator=(PlayerHandler const & rhs);

	void			addPlayer(Player player);
	Player			* getPlayer(unsigned int id);
	void			routine(Screen & screen);
	void			reset();

private:
	void			delPlayer(t_player *player);

	t_player		*_players;
	unsigned int	_nbPlayers;
};

#endif
