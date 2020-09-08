// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/29 11:28:45 by root              #+#    #+#             //
//   Updated: 2018/06/29 12:19:57 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include "Pony.hpp"

static void		ponyOnTheHeap( void )
{
	std::cout << "*** PONY ON STACK ***" << std::endl;
	std::cout << "*** Ponies alive now: " << Pony::nbPonies << std::endl;
	Pony	*pony;

	pony = new Pony(std::string("purple"), std::string("yellow"), std::string("spit flames"));

	pony->show();
	pony->use_ability();
	std::cout << "*** Ponies alive now: " << Pony::nbPonies << std::endl;
	delete pony;
}

static void	ponyOnTheStack( void )
{
	std::cout << "*** PONY ON HEAP ***" << std::endl;
	std::cout << "*** Ponies alive now: " << Pony::nbPonies << std::endl;
	Pony		pony(std::string("white"), std::string("light blue"), std::string("fly"));

	pony.show();
	pony.use_ability();
	std::cout << "*** Ponies alive now: " << Pony::nbPonies << std::endl;
}

int		main()
{
	ponyOnTheHeap();
	ponyOnTheStack();

	std::cout << "*** Ponies alive now: " << Pony::nbPonies << std::endl;
	return 0;
}
