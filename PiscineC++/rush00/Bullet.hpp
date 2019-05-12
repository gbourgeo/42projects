// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Bullet.hpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/10/06 16:36:35 by gbourgeo          #+#    #+#             //
//   Updated: 2018/10/06 20:01:11 by gbourgeo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef BULLET_HPP
# define BULLET_HPP

#include "Movable.hpp"

class Bullet: public Movable
{
public:
	Bullet();
	Bullet(char name, int x, int y, double speed, int damage, bool direction);
	Bullet(Bullet const & src);
	~Bullet();
	Bullet & operator=(Bullet const & rhs);

	// Simple check -> (y <= 1)
	bool	isArrived() const;

	char	getName() const;
	int		getDamage() const;
	
protected:
	char	_name;
	int		_damage;
};

#endif
