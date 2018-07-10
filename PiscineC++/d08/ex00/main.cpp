// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/10 13:27:30 by root              #+#    #+#             //
//   Updated: 2018/07/10 13:40:22 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include <vector>
#include <list>
#include "easyfind.hpp"

int main()
{
	std::vector<int>	ar2;
	std::list<int>		ar3;

	ar2.push_back(0);
	ar2.push_back(2);
	ar2.push_back(4);
	ar2.push_back(6);
	ar2.push_back(8);
	ar2.push_back(10);

	ar3.push_back(1);
	ar3.push_back(3);
	ar3.push_back(5);
	ar3.push_back(7);
	ar3.push_back(9);
	ar3.push_back(11);

	for (int i = 0; i < 10; i++) {
		try {
			easyfind(ar2, i);
			std::cout << "Found " << i << " in <vector> !!!" << std::endl;
		} catch (std::exception &e) {
			std::cout << "Not Found " << i << " in <vector> ..." << std::endl;
		}
	}

	std::cout << std::endl;

	for (int i = 0; i < 10; i++) {
		try {
			easyfind(ar3, i);
			std::cout << "Found " << i << " in <list> !!!" << std::endl;
		} catch (std::exception &e) {
			std::cout << "Not Found " << i << " in <list> ..." << std::endl;
		}
	}

	return 0;
}
