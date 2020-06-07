/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bullet.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 16:36:35 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/06/07 14:52:19 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BULLET_HPP
# define BULLET_HPP

# include "Movable.hpp"

class PlayerHandler;
class EnnemyHandler;
class AEntities;

class Bullet: public Movable
{
public:
	Bullet();
	Bullet(char name, int x, int y, double speed, int damage, AEntities *owner, bool direction);
	Bullet(Bullet const & src);
	~Bullet();
	Bullet & operator=(Bullet const & rhs);

	// Check if Bullet get out of MAP
	bool	isOut() const;
	bool	touched(PlayerHandler & p) const;
	bool	touched(EnnemyHandler & e) const;

	char	getName() const;

protected:
	char		_name;
	int			_damage;
	AEntities	*_owner;
};

#endif
