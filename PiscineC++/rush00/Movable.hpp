/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Movable.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 18:19:27 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/06/05 15:44:12 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOVABLE_HPP
# define MOVABLE_HPP

#include <sys/time.h>

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
	void	updateLastMove(void);

protected:
	Movable();

	int		_x;
	int		_y;
	double	_speed;
	bool	_direction;
	int		_xSave;
	int		_ySave;
	timeval	_lastMove;
};

#endif
