// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/10 13:40:51 by root              #+#    #+#             //
//   Updated: 2018/07/10 15:00:45 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <ctime>
#include <cstdlib>
#include <iostream>
#include "span.hpp"

int main()
{
	Span	sp(13);

	sp.addNumber(5);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);

	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;

	Span	sp2(30000);

	std::srand(std::time(NULL));
	for (int i = 0; i < 30000; i++) {
		sp2.addNumber(std::rand());
	}
	std::cout << sp2.shortestSpan() << std::endl;
	std::cout << sp2.longestSpan() << std::endl;
	
	return 0;
}
