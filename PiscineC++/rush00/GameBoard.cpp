/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GameBoard.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 14:13:35 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/06/05 14:52:33 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GameBoard.hpp"

GameBoard::GameBoard():
	_timing(0)
{}

GameBoard::GameBoard(GameBoard const & src)
{
	*this = src;
}

GameBoard::~GameBoard()
{}

GameBoard & GameBoard::operator=(GameBoard const & rhs)
{
	if (this != &rhs)
	{
		this->_timing = rhs.getTiming();
	}
	return *this;
}

time_t GameBoard::getTiming() const
{
	return this->_timing;
}

void GameBoard::gameStart()
{
	time(&this->_timing);
}
