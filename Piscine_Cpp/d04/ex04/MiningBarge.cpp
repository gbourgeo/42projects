// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   MiningBarge.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/06 00:45:07 by gbourgeo          #+#    #+#             //
//   Updated: 2018/07/06 03:09:50 by gbourgeo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "MiningBarge.hpp"

MiningBarge::MiningBarge()
{
	for (int i = 0; i < MINING_LASER_MAX; i++) {
		this->_laser[i] = 0;
	}
}

MiningBarge::MiningBarge(MiningBarge const & src)
{
	*this = src;
}

MiningBarge & MiningBarge::operator=(MiningBarge const & rhs)
{
	if (this != &rhs)
	{
		for (int i = 0; i < MINING_LASER_MAX; i++) {
			this->_laser[i] = rhs.getMiningLaser(i);
		}
	}
	return *this;
}

MiningBarge::~MiningBarge()
{
	for (int i = 0; i < MINING_LASER_MAX; i++) {
		if (this->_laser[i])
			delete this->_laser[i];
		this->_laser[i] = 0;
	}
}

void MiningBarge::equip(IMiningLaser *laser)
{
	for (int i = 0; i < MINING_LASER_MAX; i++) {
		if (this->_laser[i] == 0) {
			this->_laser[i] = laser;
			break ;
		}
	}
}

void MiningBarge::mine(IAsteroid *asteroid) const
{
	for (int i = 0; i < MINING_LASER_MAX; i++) {
		if (this->_laser[i])
			this->_laser[i]->mine(asteroid);
	}
}

IMiningLaser *MiningBarge::getMiningLaser(int idx) const
{
	if (idx < 0 || idx >= MINING_LASER_MAX)
		return 0;
	return this->_laser[idx];
}
