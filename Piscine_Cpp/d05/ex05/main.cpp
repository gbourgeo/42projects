// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/06 12:25:06 by root              #+#    #+#             //
//   Updated: 2018/07/08 06:24:39 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "CentralBureaucracy.hpp"
#include "Bureaucrat.hpp"
#include "Intern.hpp"
#include "OfficeBlock.hpp"
#include "Form.hpp"

int main()
{
	CentralBureaucracy	central;

	std::string names[] = {"Paul", "Henry", "Katy", "Maria", "Henriette", "Paulo",
							"Homer", "Ronald", "Pedro", "Pablo", "Ron", "Annie",
						   "Louis", "Patrick", "Conrad", "John", "Marie", "Loic",
						   "Carra", "Connie"};
	int			priv[] = { 1, 20, 100, 43, 25, 5,
						   13, 149, 99, 10, 75, 89,
						   32, 3, 78, 102, 16, 66,
						   13, 12 };
	std::string queue[] = {"Tree", "Fork", "Moms", "Harry", "Potter", "Coming",
						   "Summer", "Paul", "Swimming Pool", "Pain", "Bread", "Saussage",
						   "Orange", "Birthday", "Happy Feet", "Morello", "Catch", "Foot",
						   "Sports", "Hockey" };

	for (int i = 0; i < 20; i++) {
		central.addBureaucrat(new Bureaucrat(names[i], priv[i]));
		central.queueUp(queue[i]);
	}
	central.doBureaucracy();
}
