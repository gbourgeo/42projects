// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   DeepCoreMiner.hpp                                  :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/05 22:48:09 by gbourgeo          #+#    #+#             //
//   Updated: 2018/07/06 03:03:18 by gbourgeo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef DEEPCOREMINER_HPP
# define DEEPCOREMINER_HPP

# include "IAsteroid.hpp"
# include "IMiningLaser.hpp"

class DeepCoreMiner : public IMiningLaser
{
public:
	DeepCoreMiner();
	DeepCoreMiner(DeepCoreMiner const & src);
	DeepCoreMiner & operator=(DeepCoreMiner const & rhs);
	~DeepCoreMiner();
	
	void		mine(IAsteroid *);
};

#endif
