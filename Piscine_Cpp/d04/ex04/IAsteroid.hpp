// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   IAsteroid.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/06 00:20:40 by gbourgeo          #+#    #+#             //
//   Updated: 2018/07/06 03:02:37 by gbourgeo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef IASTEROID_HPP
# define IASTEROID_HPP

# include <iostream>

class StripMiner;
class DeepCoreMiner;

class IAsteroid
{
public:
	virtual ~IAsteroid() {}
	virtual std::string beMined(StripMiner *) const = 0;
	virtual std::string beMined(DeepCoreMiner *) const = 0;
	virtual std::string getName() const = 0;
};

#endif
