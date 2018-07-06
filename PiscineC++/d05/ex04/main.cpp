// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/06 12:25:06 by root              #+#    #+#             //
//   Updated: 2018/07/06 20:44:34 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Intern.hpp"
#include "Form.hpp"

int main()
{
	Intern	paul;
	Form	*form = 0;

	form = paul.makeForm("toto", "tata");
	if (form) {
		std::cout << *form;
		delete form;
		form = 0;
	}
	form = paul.makeForm("shrubbery creation", "Tree");
	if (form) {
		std::cout << *form;
		delete form;
		form = 0;
	}
	form = paul.makeForm("robotomy request", "Blender");
	if (form) {
		std::cout << *form;
		delete form;
		form = 0;
	}
	form = paul.makeForm("presidential pardon", "Bill");
	if (form) {
		std::cout << *form;
		delete form;
		form = 0;
	}
	return 0;
}
