// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/09 21:33:55 by gbourgeo          #+#    #+#             //
//   Updated: 2018/07/09 23:39:08 by gbourgeo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include "Array.thh"

int main()
{
	Array<int>	in(13);
	std::cout << "int: ";
	for (unsigned int i = 0; i < in.getNbElems(); i++) {
		std::cout << in.getElem(i) << " ";
	}
	std::cout << std::endl;

	Array<float>	fl(13);
	std::cout << "float: ";
	for (unsigned int i = 0; i < fl.getNbElems(); i++) {
		std::cout << fl.getElem(i) << " ";
	}
	std::cout << std::endl;
	
	Array<std::string> st(13);
	std::cout << "string: ";
	for (unsigned int i = 0; i < st.getNbElems(); i++) {
		std::cout << st.getElem(i) << " ";
	}
	std::cout << std::endl;

	return 0;
}
