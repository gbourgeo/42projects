// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Movable.hpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/10/06 18:19:27 by gbourgeo          #+#    #+#             //
//   Updated: 2018/10/07 20:46:40 by gbourgeo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef MOVABLE_HPP
# define MOVABLE_HPP

//#include "main.hpp"
//#include "Logger.hpp"
#include <sys/time.h>
#include <iostream>

class Movable
{
public:
	Movable(int x, int y, double speed, bool direction);
	Movable(Movable const &src);
	~Movable();
	Movable & operator=(Movable const & rhs);

	int		getX() const;
	int		getY() const;
	double	getSpeed() const;
	timeval	getLastMove() const;
	void	move(int x, int y);
	void	updatePosition(void);
	void	ratioUpdate(int diff);
	void	updateLastMove(void);

protected:
	Movable();

	int		_x;
	int		_y;
	double	_speed;
	bool	_direction;
	timeval	_lastMove;
};

#endif
