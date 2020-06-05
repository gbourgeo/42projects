/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EnnemyHandler.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 10:53:52 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/06/05 16:21:15 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "EnnemyHandler.hpp"
#include "main.hpp"

EnnemyHandler::EnnemyHandler(): _list(nullptr), _nbEnnemies(0)
{}

EnnemyHandler::~EnnemyHandler()
{
	for (t_ennemy *ptr = this->_list; ptr; ptr = this->_list)
	{
		this->_list = ptr->next;
		delete ptr->ennemy;
		delete ptr;
	}
}

EnnemyHandler::EnnemyHandler(EnnemyHandler const & src)
{
	*this = src;
}

EnnemyHandler & EnnemyHandler::operator=(EnnemyHandler const & rhs)
{
	if (this != &rhs)
	{
		for (t_ennemy *ptr = rhs._list,
			*prev = nullptr,
			**next = &this->_list;
			ptr;
			ptr = ptr->next,
			prev = *next,
			next = &(*next)->next)
		{
			*next = new t_ennemy;
			(*next)->ennemy = new Ennemy(*ptr->ennemy);
			(*next)->next = nullptr;
			(*next)->prev = prev;
		}
	}
	return *this;
}

void		EnnemyHandler::addEnnemy(char name, int life, int retry, int nb, int y, 
double speed, Weapon weapon)
{
	t_ennemy	*E = nullptr;
	int			x, z;

	z = (WIDTH - 2) / (nb + 1);
	x = 0;
	for (int i = 0; i < nb; i++) {
		x += z;
		E = new t_ennemy;
		E->ennemy = new Ennemy(name, life, retry, x, y, speed, false);
		E->ennemy->equip(new Weapon(weapon));
		E->prev = nullptr;
		E->next = this->_list;
		if (E->next != nullptr)
			E->next->prev = E;
		this->_list = E;
	}
	this->_nbEnnemies += nb;
}

void		EnnemyHandler::delEnnemy(t_ennemy *ennemy)
{
	t_ennemy	*ptr;

	ptr = this->_list;
	while (ptr)
		if (ptr == ennemy)
		{
			if (ptr->prev)
				ptr->prev->next = ptr->next;
			else
				this->_list = ptr->next;
			if (ptr->next)
				ptr->next->prev = ptr->prev;
			delete ptr->ennemy;
			delete ptr;
			this->_nbEnnemies -= 1;
			return ;
		}
		else
			ptr = ptr->next;
}

Ennemy		*EnnemyHandler::getEnnemy(unsigned int id)
{
	t_ennemy	*ptr;

	ptr = this->_list;
	if (id == 0 || id > this->_nbEnnemies)
		return nullptr;
	while (--id)
		ptr = ptr->next;
	return ptr->ennemy;
}

void		EnnemyHandler::shoot(BulletHandler & shots)
{
	for (t_ennemy *ptr = this->_list; ptr; ptr = ptr->next)
	{
		shots.addShot(ptr->ennemy->shoot());
	}
}

void		EnnemyHandler::routine(Screen & screen)
{
	for (t_ennemy *ptr = this->_list; ptr; ptr = ptr->next)
	{
		if (ptr->ennemy->getLife() == 0)
		{
			if (ptr->ennemy->getRetry() == 0)
				delEnnemy(ptr);
			else
				ptr->ennemy->deathAnimation();
		}
		mvwprintw(screen.getWindow(),
			ptr->ennemy->getY(),
			ptr->ennemy->getX(),
			"%c",
			ptr->ennemy->getName());
	}
}
