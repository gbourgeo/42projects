// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/06 12:25:06 by root              #+#    #+#             //
//   Updated: 2018/07/06 15:02:41 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Bureaucrat.hpp"

int main()
{
	Bureaucrat paul("Paul", 1);
	Bureaucrat annie("Annie", 100);
	Form formA("Formulary A", 10, 10);
	Form formB("Formulary B", 100, 99);

	std::cout << paul;
	std::cout << annie;
	std::cout << formA;
	std::cout << formB;

	try {
		annie.signForm(formA);
	} catch (std::exception &e) {
		std::cout << "Exception catched: " ;
		std::cout << e.what() << std::endl;
	}
	std::cout << formA;
	try {
		annie.signForm(formB);
	} catch (std::exception &e) {
		std::cout << "Exception catched: " ;
		std::cout << e.what() << std::endl;
	}
	std::cout << formB;

	try {
		paul.signForm(formA);
	} catch (std::exception &e) {
		std::cout << "Exception catched: " ;
		std::cout << e.what() << std::endl;
	}
	std::cout << formA;
	try {
		paul.signForm(formB);
	} catch (std::exception &e) {
		std::cout << "Exception catched: " ;
		std::cout << e.what() << std::endl;
	}
	std::cout << formB;

	try {
		Form A("Hello", -1, 10);
	} catch (std::exception & e) {
		std::cout << "Exception catched: " ;
		std::cout << e.what() << std::endl;
	}

	try {
		Form A("Hello", 1, 12345678);
	} catch (std::exception & e) {
		std::cout << "Exception catched: " ;
		std::cout << e.what() << std::endl;
	}
	
	return 0;
}
