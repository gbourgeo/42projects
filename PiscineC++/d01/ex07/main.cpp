// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/29 18:20:54 by root              #+#    #+#             //
//   Updated: 2018/06/29 18:55:05 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include <fstream>
#include <string>

int main(int ac, char **av)
{
	std::ifstream			file;
	std::string				buff;
	std::string				content;
	std::ofstream			out;
	std::string				outname;
	std::size_t				found;

	if (ac != 4) {
		std::cerr << "Usage:" << std::endl;
		std::cerr << "\t" << av[0] << " [filename] \"string 1\" \"string 2\"" << std::endl;
		return 1;
	}
	if (!*av[2] || !*av[3]) {
		std::cerr << "ERROR: one string is empty." << std::endl;
		return 1;
	}
	file.open(av[1]);
	if (!file.is_open()) {
		std::cerr << "Error while opening file " << av[1] << std::endl;
		return 1;
	}
	outname = std::string(av[1]) + std::string(".replace");
	out.open(outname.c_str(), std::ios::trunc);
	if (!out.is_open()) {
		std::cerr << "Error while opening file " << outname << std::endl;
		return 1;
	}
	while (getline(file, buff)) {
		content += buff + "\n";
	}
	outname = av[2];
	found = content.find(outname);
	while (found != std::string::npos) {
		content.replace(content.find(outname), outname.length(), av[3]);
		found = content.find(outname);
	}
	out << content;
	file.close();
	out.close();
	return 0;
}
