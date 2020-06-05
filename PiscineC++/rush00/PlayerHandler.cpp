/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PlayerHandler.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 12:41:15 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/06/05 16:19:49 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PlayerHandler.hpp"

PlayerHandler::PlayerHandler(): _players(nullptr), _nbPlayers(0)
{}

PlayerHandler::~PlayerHandler()
{
	for (t_player *ptr = this->_players; ptr; ptr = this->_players)
	{
		this->_players = ptr->next;
		delete ptr->player;
		delete ptr;
	}
}

PlayerHandler::PlayerHandler(PlayerHandler const & src)
{
	*this = src;
}

PlayerHandler & PlayerHandler::operator=(PlayerHandler const & rhs)
{
	if (this != &rhs)
	{
		for (t_player *ptr = rhs._players,
			*prev = nullptr,
			**next = &this->_players;
			ptr;
			ptr = ptr->next,
			prev = *next,
			next = &(*next)->next)
		{
			*next = new t_player;
			(*next)->player = new Player(*ptr->player);
			(*next)->next = nullptr;
			(*next)->prev = prev;
		}
	}
	return *this;
}

void		PlayerHandler::addPlayer(Player player)
{
	t_player	*ptr;

	ptr = this->_players;
	this->_players = new t_player;
	this->_players->player = new Player(player);
	this->_players->prev = nullptr;
	this->_players->next = ptr;
	if (ptr)
		ptr->prev = this->_players;
	this->_nbPlayers += 1;
}

void		PlayerHandler::delPlayer(t_player *player)
{
	t_player		*ptr;

	ptr = this->_players;
	while (ptr)
		if (ptr == player)
		{
			if (ptr->prev)
				ptr->prev->next = ptr->next;
			else
				this->_players = ptr->next;
			if (ptr->next)
				ptr->next->prev = ptr->prev;
			delete ptr->player;
			delete ptr;
			this->_nbPlayers -= 1;
			return ;
		}
		else
		{
			ptr = ptr->next;
		}
		
}

Player		* PlayerHandler::getPlayer(unsigned int id)
{
	t_player	*ptr;

	ptr = this->_players;
	if (id == 0 || id > this->_nbPlayers)
		return nullptr;
	while (--id > 0)
		ptr = ptr->next;
	return ptr->player;
}

void		PlayerHandler::routine(Screen & screen)
{
	for (t_player *ptr = this->_players; ptr; ptr = ptr->next)
	{
		if (ptr->player->getLife() == 0)
		{
			if (ptr->player->getRetry() == 0)
				PlayerHandler::delPlayer(ptr);
			else
			{
				ptr->player->deathAnimation();
			}
		}
		mvwprintw(screen.getWindow(),
			ptr->player->getY(),
			ptr->player->getX(),
			"%c",
			ptr->player->getName());
	}
}
