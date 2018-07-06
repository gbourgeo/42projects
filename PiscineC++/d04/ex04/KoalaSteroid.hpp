// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   BocalSteroid.hpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/06 00:31:10 by gbourgeo          #+#    #+#             //
//   Updated: 2018/07/06 00:41:10 by gbourgeo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef BOCALSTEROID_HPP
# define BOCALSTEROID_HPP

# include "StripMiner.hpp"
# include "DeepCoreMiner.hpp"
# include "IAsteroid.hpp"

class BocalSteroid : public IAsteroid
{
public:
	BocalSteroid();
	BocalSteroid(BocalSteroid const & src);
	BocalSteroid & operator=(BocalSteroid const & rhs);
	~BocalSteroid();

	std::string		beMined(StripMiner *) const;
	std::string		beMined(DeepCoreMiner *) const;
	std::string		getName() const;
private:
	std::string		_name;
};

#endif

