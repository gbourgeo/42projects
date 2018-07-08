/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 00:33:42 by gbourgeo          #+#    #+#             */
//   Updated: 2018/07/09 01:07:14 by gbourgeo         ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base *generate(void)
{
	int i = (std::rand() * 7) % 3;

	if (i < 0)
		i = -i;
	std::cout << "\e[33;1mRandomization fall : ";
	if (i == 0) {
		std::cout << "A\e[0m" << std::endl;
		return new A;
	}
	if (i == 1) {
		std::cout << "B\e[0m" << std::endl;
		return new B;
	}
	std::cout << "C\e[0m" << std::endl;
	return new C;
}

void identify_from_pointer( Base *p )
{
	A *a = dynamic_cast<A *>(p);
	if (a != NULL)
		std::cout << "A" << std::endl;
	B *b = dynamic_cast<B *>(p);
	if (b != NULL)
		std::cout << "B" << std::endl;
	C *c = dynamic_cast<C *>(p);
	if (c != NULL)
		std::cout << "C" << std::endl;
}

void identify_from_reference( Base & p )
{
	try {
		A &a = dynamic_cast<A &>(p);
		std::cout << "A" << std::endl;
		(void)a;
	} catch (std::bad_cast &e){}
	try {
		B &b = dynamic_cast<B &>(p);
		std::cout << "B" << std::endl;
		(void)b;
	} catch (std::bad_cast &e){}
	try {
		C &c = dynamic_cast<C &>(p);
		std::cout << "C" << std::endl;
		(void)c;
	} catch (std::bad_cast &e){}
}

int main()
{
	Base *p;

	std::srand(std::time(NULL));
	for (int i = 0; i < 10; i++) {
		p = generate();
		std::cout << "Identify From Pointer: ";
		identify_from_pointer(p);
		std::cout << "Identify from Reference: ";
		identify_from_reference(*p);
		delete p;
	}
	return 0;
}
