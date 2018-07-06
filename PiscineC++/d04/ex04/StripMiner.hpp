// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   StripMiner.hpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/05 22:57:36 by gbourgeo          #+#    #+#             //
//   Updated: 2018/07/06 03:05:13 by gbourgeo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef STRIPMINER_HPP
# define STRIPMINER_HPP

# include "IAsteroid.hpp"
# include "IMiningLaser.hpp"

class StripMiner : public IMiningLaser
{
public:
	StripMiner();
	StripMiner(StripMiner const & src);
	StripMiner & operator=(StripMiner const & rhs);
	~StripMiner();

	void		mine(IAsteroid *);
};

#endif
