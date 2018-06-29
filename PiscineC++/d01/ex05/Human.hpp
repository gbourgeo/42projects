// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Human.hpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/29 15:37:07 by root              #+#    #+#             //
//   Updated: 2018/06/29 15:50:30 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef HUMAN_HPP
# define HUMAN_HPP

#include <string>
#include "Brain.hpp"

class Human
{
public:
	Human();
	~Human();

	std::string		identify() const;
	const Brain &	getBrain();

private:
	const Brain		_brain;
};

#endif
