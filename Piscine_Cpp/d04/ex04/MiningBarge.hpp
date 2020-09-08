// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   MiningBarge.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/06 00:44:56 by gbourgeo          #+#    #+#             //
//   Updated: 2018/07/06 02:59:06 by gbourgeo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef MININGBARGE
# define MININGBARGE

# define MINING_LASER_MAX	4

# include "IMiningLaser.hpp"

class MiningBarge
{
public:
	MiningBarge();
	MiningBarge(MiningBarge const & src);
	MiningBarge & operator=(MiningBarge const & rhs);
	~MiningBarge();

	void equip(IMiningLaser *);
	void mine(IAsteroid *) const;
	IMiningLaser *getMiningLaser(int) const;

private:
	IMiningLaser *	_laser[MINING_LASER_MAX];
};

#endif
