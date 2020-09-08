// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ex04.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/29 14:39:35 by root              #+#    #+#             //
//   Updated: 2018/06/29 14:41:37 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include <string>

int main()
{
	std::string		str("HI THIS IS BRAIN");
	std::string		*ptr = &str;
	std::string		&ref = str;

	std::cout << "[PTR] => " << *ptr << std::endl;
	std::cout << "[REF] => " << ref << std::endl;
	
	return 0;
}
