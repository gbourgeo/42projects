// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Weapon.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/10/06 14:58:43 by gbourgeo          #+#    #+#             //
//   Updated: 2018/10/06 20:03:47 by gbourgeo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef WEAPON_HPP
# define WEAPON_HPP

#include <ctime>

#include "Bullet.hpp"

class Weapon
{
public:
	Weapon(double shootRate, double bulletSpeed, char bulletName, int bulletDamage);
	Weapon(Weapon const & src);
	~Weapon();
	Weapon & operator=(Weapon const & rhs);

	double		getShootRate() const;
	double		getBulletSpeed() const;
	char		getBulletName() const;
	int			getBulletDamage() const;
	timeval		getLastShot() const;
	void		setLastShot();
	bool		canShoot() const;

	Bullet		*shoot(int x, int y, bool direction);

protected:
	Weapon();

	double		_shootRate;
	double		_bulletSpeed;
	char		_bulletName;
	int			_bulletDamage;
	timeval		_lastShot;
};

#endif
