/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameBoard.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 14:13:33 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/06/05 14:13:37 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAMEBOARD_HPP
# define GAMEBOARD_HPP

#include <ctime>

class GameBoard
{
public:
	GameBoard();
	GameBoard(GameBoard const & src);
	~GameBoard();
	GameBoard & operator=(GameBoard const & rhs);

	time_t	getTiming() const;
	void	gameStart();
	
private:
	time_t	_timing;
};

#endif
