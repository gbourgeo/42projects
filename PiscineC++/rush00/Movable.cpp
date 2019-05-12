// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Movable.cpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/10/06 18:24:13 by gbourgeo          #+#    #+#             //
//   Updated: 2018/10/07 20:46:56 by gbourgeo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Movable.hpp"

Movable::Movable():
	_x(0), _y(0),_speed(0.0)
{
	timeval now;
	gettimeofday(&now, NULL);
	this->_lastMove = now;
}

Movable::Movable(int x, int y, double speed, bool direction):
	_x(x), _y(y), _speed(speed), _direction(direction)
{
	timeval now;
	gettimeofday(&now, NULL);
	this->_lastMove = now;
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
		this->_x = rhs.getX();
		this->_y = rhs.getY();
		this->_speed = rhs.getSpeed();
		this->_lastMove = rhs.getLastMove();
	}
	return *this;
}

// Update Position itself from last move + speed
void	Movable::updatePosition(void) {
	timeval current;
	gettimeofday(&current, NULL);
	timeval last = this->getLastMove();

    int diff = (((current.tv_sec - last.tv_sec) * 1000000) +
            (current.tv_usec - last.tv_usec))/1000;

	this->ratioUpdate(diff);
}

void	Movable::ratioUpdate(int diff) {
	int positionDiff = diff / ((1 / this->getSpeed()) * 1000);

	if (positionDiff > 0) {
		this->_y = this->_direction ? this->_y - positionDiff : this->_y + positionDiff;
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
	timeval now;
	gettimeofday(&now, NULL);
	this->_lastMove = now;
}

void Movable::move(int x, int y)
{
	this->_x = x;
	this->_y = y;
	this->updateLastMove();
}
