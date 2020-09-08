// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/09 21:33:55 by gbourgeo          #+#    #+#             //
//   Updated: 2018/07/12 21:52:15 by gbourgeo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include "Array.thh"

int main()
{
	Array<int>	in(13);
	std::cout << "int: ";
	for (unsigned int i = 0; i < in.size(); i++) {
		std::cout << in[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "Copy constructor" << std::endl;
	Array<int>	copy(in);
	std::cout << "copy: ";
	for (unsigned int i = 0; i < copy.size(); i++) {
		std::cout << copy[i] << " ";
	}
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "Assignation constructor && Elems unique per class" << std::endl;
	copy = in;
	for (unsigned int i = 0; i < copy.size(); i++) {
		copy[i] = i;
	}
	std::cout << "int: ";
	for (unsigned int i = 0; i < in.size(); i++) {
		std::cout << in[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "assign: ";
	for (unsigned int i = 0; i < copy.size(); i++) {
		std::cout << copy[i] << " ";
	}
	std::cout << std::endl;
	std::cout << std::endl;

	std::cout << "Exception on out of range index" << std::endl;
	try {
		std::cout << "copy[13]: ";
		std::cout << copy[13] << std::endl;
	} catch (std::exception & e) {
		std::cout << e.what() << std::endl;
	}

	Array<float>	fl(13);
	std::cout << "float: ";
	for (unsigned int i = 0; i < fl.size(); i++) {
		std::cout << fl[i] << " ";
	}
	std::cout << std::endl;

	Array<double>	db(13);
	std::cout << "double: ";
	for (unsigned int i = 0; i < db.size(); i++) {
		std::cout << db[i] << " ";
	}
	std::cout << std::endl;

	Array<char>	ch(13);
	std::cout << "char: ";
	for (unsigned int i = 0; i < ch.size(); i++) {
		std::cout << ch[i] << " ";
	}
	std::cout << std::endl;

	return 0;
}
