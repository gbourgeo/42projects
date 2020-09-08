// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   IMiningLaser.hpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/05 22:46:03 by gbourgeo          #+#    #+#             //
//   Updated: 2018/07/05 22:53:43 by gbourgeo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef IMININGLASER_HPP
# define IMININGLASER_HPP

class IAsteroid;

class IMiningLaser
{
public:
	virtual ~IMiningLaser() {}
	virtual void mine(IAsteroid*) = 0;
};

#endif
