// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/06 12:25:06 by root              #+#    #+#             //
//   Updated: 2018/07/08 03:11:08 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Bureaucrat.hpp"
#include "Intern.hpp"
#include "OfficeBlock.hpp"
#include "Form.hpp"

int main()
{
	OfficeBlock		A;

	try {
		A.doBureaucracy("salut", "toi");
	} catch (std::exception & e) {
		std::cout << e.what() << std::endl;
	}

	A.setIntern(new Intern());
	try {
		A.doBureaucracy("salut", "toi");
	} catch (OfficeBlock::NoInternAssignedException & e) {
		std::cout << e.what() << std::endl;
	} catch (std::exception & e) {
		std::cout << e.what() << std::endl;
	}

	A.setSigningBureaucrat(new Bureaucrat("Roger", 25));
	try {
		A.doBureaucracy("salut", "toi");
	} catch (OfficeBlock::NoSigningBureaucratException & e) {
		std::cout << e.what() << std::endl;
	} catch (std::exception & e) {
		std::cout << e.what() << std::endl;
	}

	A.setExecutingBureaucrat(new Bureaucrat("Alicia", 25));
	try {
		A.doBureaucracy("salut", "toi");
	} catch (std::exception & e) {
		std::cout << e.what() << std::endl;
	}

	Form *f;
		
	try {
		f = A.doBureaucracy("shrubbery creation", "Tree");
		std::cout << *f;
		delete f;
	} catch (std::exception & e) {
		std::cout << e.what() << std::endl;
	}
	
	try {
		f = A.doBureaucracy("robotomy request", "Zoe");
		std::cout << *f;
		delete f;
	} catch (std::exception & e) {
		std::cout << e.what() << std::endl;
	}
	try {
		f = A.doBureaucracy("presidential pardon", "Bill");
		std::cout << *f;
		delete f;
	} catch (std::exception & e) {
		std::cout << e.what() << std::endl;
	}

	A.setExecutingBureaucrat(new Bureaucrat("John", 5));
	try {
		f = A.doBureaucracy("presidential pardon", "Bill");
		std::cout << *f;
		delete f;
	} catch (std::exception & e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}
