// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/08 17:16:56 by gbourgeo          #+#    #+#             //
//   Updated: 2018/07/08 22:00:33 by gbourgeo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include "Converter.hpp"

int main(int ac, char **av)
{
	Converter	convert;

	if (ac != 2) {
		std::cerr << "Usage:" << std::endl;
		std::cerr << "\t" << av[0] << " [number]" << std::endl;
		return 1;
	}
	convert.doConversions(av[1]);
	return 0;
}
