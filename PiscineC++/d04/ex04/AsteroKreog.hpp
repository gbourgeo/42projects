// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AsteroBocal.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/06 00:22:47 by gbourgeo          #+#    #+#             //
//   Updated: 2018/07/06 00:40:44 by gbourgeo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ASTEROBOCAL_HPP
# define ASTEROBOCAL_HPP

# include "StripMiner.hpp"
# include "DeepCoreMiner.hpp"
# include "IAsteroid.hpp"

class AsteroBocal : public IAsteroid
{
public:
	AsteroBocal();
	AsteroBocal(AsteroBocal const & src);
	AsteroBocal & operator=(AsteroBocal const & rhs);
	~AsteroBocal();

	std::string		beMined(StripMiner *) const;
	std::string		beMined(DeepCoreMiner *) const;
	std::string		getName() const;
private:
	std::string		_name;
};

#endif
