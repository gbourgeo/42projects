// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/06 12:25:06 by root              #+#    #+#             //
//   Updated: 2018/07/06 12:42:32 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Bureaucrat.hpp"

int main()
{
	try {
		Bureaucrat	jim("Jim", 160);
	} catch (std::exception & e) {
		std::cout << e.what() << std::endl;
	}
	try {
		Bureaucrat	jim("Jim", 0);
	} catch (std::exception & e) {
		std::cout << e.what() << std::endl;
	}

	Bureaucrat paul("Paul", 1);
	Bureaucrat annie("Annie", 150);

	std::cout << paul;
	std::cout << annie;

	try {
		paul.incrementGrade();
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	try {
		annie.decrementGrade();
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	std::cout << paul;
	std::cout << annie;

	paul.decrementGrade();
	annie.incrementGrade();

	std::cout << paul;
	std::cout << annie;

	return 0;
}
