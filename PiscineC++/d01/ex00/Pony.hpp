// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Pony.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/29 11:28:42 by root              #+#    #+#             //
//   Updated: 2018/06/29 11:53:36 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef PONY_HPP
# define PONY_HPP

#include <string>

class Pony
{
public:
	Pony(std::string pony_color, std::string tail_color, std::string ability);
	~Pony( void );

	void			show( void );
	void			use_ability( void );

	static int		nbPonies;

private:
	std::string		_pony_color;
	std::string		_tail_color;
	std::string		_ability;
};

#endif /* PONY_HPP */
