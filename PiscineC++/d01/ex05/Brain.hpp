// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Brain.hpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/29 14:43:23 by root              #+#    #+#             //
//   Updated: 2018/06/29 15:51:19 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef BRAIN_HPP
# define BRAIN_HPP

#include <string>

class Brain
{
public:
	Brain();
	~Brain();

	std::string identify() const;
};

#endif /* BRAIN_HPP */
