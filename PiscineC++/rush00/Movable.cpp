/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Movable.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 18:24:13 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/06/05 15:45:18 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Movable.hpp"
#include <iostream>

Movable::Movable():
	_x(0), _y(0), _speed(0.0), _direction(false), _xSave(0), _ySave(0)
{
	gettimeofday(&this->_lastMove, NULL);
}

Movable::Movable(int x, int y, double speed, bool direction):
	_x(x), _y(y), _speed(speed), _direction(direction), _xSave(x), _ySave(y)
{
	gettimeofday(&this->_lastMove, NULL);
}

Movable::~Movable()
{}

Movable::Movable(Movable const & src)
{
	*this = src;
}

Movable & Movable::operator=(Movable const & rhs)
{
	if (this != &rhs)
	{
		this->_x = rhs._x;
		this->_y = rhs._y;
		this->_speed = rhs._speed;
		this->_direction = rhs._direction;
		this->_xSave = rhs._xSave;
		this->_ySave = rhs._ySave;
		this->_lastMove = rhs._lastMove;
	}
	return *this;
}

// Update Position itself from last move + speed
void	Movable::updatePosition(void) {
	timeval current;

	gettimeofday(&current, NULL);
	unsigned long diff = current.tv_sec * 1000000
		- this->_lastMove.tv_sec * 1000000
		+ current.tv_usec
		- this->_lastMove.tv_usec;
	if (diff > (1000000.0 / this->_speed)) {
		this->_y = this->_direction ? this->_y - 1 : this->_y + 1;
		this->updateLastMove();
	}
}

int Movable::getX() const
{
	return this->_x;
}

int Movable::getY() const
{
	return this->_y;
}

double Movable::getSpeed() const
{
	return this->_speed;
}

timeval Movable::getLastMove() const
{
	return this->_lastMove;
}

void	Movable::updateLastMove(void) {
	gettimeofday(&this->_lastMove, NULL);
}

void Movable::move(int x, int y)
{
	this->_x = x;
	this->_y = y;
	this->updateLastMove();
}
