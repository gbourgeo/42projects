/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BulletHandler.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 13:45:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/06/07 15:30:37 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BulletHandler.hpp"

BulletHandler::BulletHandler()
{
	this->_shots = nullptr;
}

BulletHandler::~BulletHandler()
{
	for (t_shot *ptr = this->_shots, *next = nullptr; ptr; ptr = next)
	{
		next = ptr->next;
		delete ptr->shot;
		delete ptr;
	}
	this->_shots = nullptr;
}

BulletHandler::BulletHandler(BulletHandler const & src)
{
	*this = src;
}

BulletHandler & BulletHandler::operator=(BulletHandler const & rhs)
{
	if (this != &rhs)
	{
		for (t_shot **tptr = &this->_shots,
			*tprev = nullptr,
			*rptr = rhs._shots; rptr; rptr = rptr->next)
		{
			*tptr = new t_shot;
			(*tptr)->shot = new Bullet(*rptr->shot);
			(*tptr)->prev = tprev;
			tprev = *tptr;
			tptr = &(*tptr)->next;
		}
	}
	return *this;
}

void BulletHandler::addShot(Bullet *b)
{
	t_shot		*ptr;

	if (b != nullptr)
	{
		ptr = this->_shots;
		this->_shots = new t_shot;
		this->_shots->shot = b;
		this->_shots->next = ptr;
		if (ptr)
			ptr->prev = this->_shots;
		this->_shots->prev = nullptr;
	}
}

void BulletHandler::moveShots(Screen & screen, PlayerHandler & p, EnnemyHandler & e)
{
	updateShots(p, e);
	for (t_shot *ptr = this->_shots; ptr; ptr = ptr->next)
	{
		ptr->shot->updatePosition();
		mvwprintw(screen.getWindow(),
			ptr->shot->getY(),
			ptr->shot->getX(),
			"%c",
			ptr->shot->getName());
	}
}

/*
** Did a bullet get out of screen,
** touched a player,
** or touched an ennemy ?
*/

void BulletHandler::updateShots(PlayerHandler & p, EnnemyHandler & e)
{
	t_shot 		*ptr;
	t_shot 		*next;

	ptr = this->_shots;
	while (ptr)
		if (ptr->shot->isOut() || ptr->shot->touched(p) || ptr->shot->touched(e))
		{
			if (ptr->prev)
				ptr->prev->next = ptr->next;
			else
				this->_shots = ptr->next;
			if (ptr->next)
				ptr->next->prev = ptr->prev;
			next = ptr->next;
			delete ptr->shot;
			delete ptr;
			ptr = next;
		}
		else
		{
			ptr = ptr->next;
		}
}

void		BulletHandler::reset()
{
	for (t_shot *ptr = this->_shots; ptr; ptr = this->_shots)
	{
		this->_shots = ptr->next;
		delete ptr->shot;
		delete ptr;
	}
	this->_shots = nullptr;
}
