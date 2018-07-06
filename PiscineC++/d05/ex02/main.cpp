// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/06 12:25:06 by root              #+#    #+#             //
//   Updated: 2018/07/06 18:03:26 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main()
{
	Bureaucrat diego("Diego", 35);
	Bureaucrat tom("Tom", 140);
	Bureaucrat sylvie("Sylvie", 150);

	ShrubberyCreationForm A("home");

	std::cout << diego;
	std::cout << tom;
	std::cout << A;
	sylvie.executeForm(A);
	sylvie.signForm(A);
	sylvie.executeForm(A);
	std::cout << A;
	tom.executeForm(A);
	tom.signForm(A);
	tom.executeForm(A);
	std::cout << A;
	diego.executeForm(A);
	diego.signForm(A);
	diego.executeForm(A);

	RobotomyRequestForm B("Hillary");
	std::cout << B;
	sylvie.signForm(B);
	std::cout << B;
	tom.signForm(B);
	std::cout << B;
	diego.signForm(B);
	diego.executeForm(B);
	diego.executeForm(B);
	diego.executeForm(B);
	diego.executeForm(B);
	
	Bureaucrat bill("Bill", 5);
	PresidentialPardonForm C("Bill Clinton");

	std::cout << C;
	sylvie.signForm(C);
	std::cout << C;
	tom.signForm(C);
	std::cout << C;
	diego.signForm(C);
	bill.executeForm(C);
	bill.signForm(C);
	bill.executeForm(C);

	return 0;
}
