// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/29 15:42:47 by root              #+#    #+#             //
//   Updated: 2018/06/29 15:44:01 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include "Human.hpp"

int main()
{
	Human	bob;

	std::cout << bob.identify() << std::endl;
	std::cout << bob.getBrain().identify() << std::endl;
	return 0;
}
