/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ennemy.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 11:35:59 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/06/05 14:07:55 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENNEMY_HPP
# define ENNEMY_HPP

#include "AEntities.hpp"

class Bullet;

class Ennemy: public AEntities
{
public:
	Ennemy(char name, int life, int retry, int x, int y, double speed, bool direction);
	Ennemy(Ennemy const & src);
	~Ennemy();
	Ennemy & operator=(Ennemy const & rhs);

	Bullet		*shoot();

private:
	Ennemy();
};

#endif
