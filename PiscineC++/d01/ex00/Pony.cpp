// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Pony.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/29 11:30:47 by root              #+#    #+#             //
//   Updated: 2018/06/29 12:26:21 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include "Pony.hpp"

int Pony::nbPonies = 0;

Pony::Pony(std::string pony_color, std::string tail_color, std::string ability):
	_pony_color(pony_color),
	_tail_color(tail_color),
	_ability(ability)
{
	std::cout << "A " << pony_color << " Pony with " << tail_color << " tail appears !" << std::endl;
	Pony::nbPonies++;
}

Pony::~Pony( void )
{
	std::cout << "The " << _pony_color << " Pony disappears..." << std::endl;
	Pony::nbPonies--;
}

void Pony::show( void )
{
	std::string		names[7] = { "red"   , "green" , "yellow", "blue"  , "purple", "light blue",
								 "white" };
	std::string		colors[7] = {"\e[31m", "\e[32m", "\e[33m", "\e[34m", "\e[35m", "\e[36m",
								 "\e[37m"};
	int				nb = 0;
	while (nb < 7) {
		if (names[nb] == _pony_color)
			break;
		nb++;
	}
	if (nb == 7)
		nb = 6;
	std::string	fur = colors[nb];
	nb = 0;
	while (nb < 7) {
		if (names[nb] == _tail_color)
			break;
		nb++;
	}
	if (nb == 7)
		nb = 6;
	std::string	tail = colors[nb];

	std::cout << tail << "    >>\\." << std::endl;
	std::cout << fur << "   /" << "\e[5m"<< "_ " << "\e[0m" << tail << " )`." << std::endl;
	std::cout << fur << "  /  _)" << tail << "`^)`. "<< fur <<"  _.---. " << tail << "_" << std::endl;
	std::cout << fur << " (_,' \\  " << tail << "`^-)"<< fur <<"\"\"      `." << tail << "\\" << std::endl;
	std::cout << fur << "       |              | " << tail << "\\" << std::endl;
	std::cout << fur << "       \\              / " << tail << "|" << std::endl;
	std::cout << fur << "      / \\  /.___.'\\  (" << tail << "\\ (_" << std::endl;
	std::cout << fur << "     < ,\"||     \\ |`. \\" << tail << "`-'" << std::endl;
	std::cout << fur << "      \\\\ ()      )|  )/" << std::endl;
	std::cout << "      |_>|>     /_] //" << std::endl;
	std::cout << "        /_]        /_]" << colors[6] << std::endl;
}

void Pony::use_ability( void )
{
	std::cout << "In a smashing din, the pony begins to... " << _ability << " !!!" << std::endl;
}
