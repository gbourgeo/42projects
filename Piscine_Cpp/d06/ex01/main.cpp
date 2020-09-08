// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/08 22:41:50 by gbourgeo          #+#    #+#             //
//   Updated: 2018/07/09 00:26:08 by gbourgeo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cctype>

struct Data
{
	std::string s1;
	int n;
	std::string s2;
};

void		* serialize( void )
{
	Data	*str = new Data;

	for (int i = 0; i < 8; i++) {
		char c = static_cast<char>(std::rand());
		while (!std::isalnum(c))
			c = static_cast<char>(std::rand());
		str->s1 += c;
	}
	str->n = std::rand() % INT_MAX;
	for (int i = 0; i < 8; i++) {
		char c = static_cast<char>(std::rand());
		while (!std::isalnum(c))
			c = static_cast<char>(std::rand());
		str->s2 += c;
	}
	std::cout << str->s1 << str->n << str->s2 << std::endl;
	return static_cast<void *>(str);
}

Data		* deserialize( void *raw )
{
	return reinterpret_cast<Data *>(raw);
}

int main()
{
	void			*raw;
	Data			*data;

	std::srand(std::time(NULL));
	raw = serialize();
	data = deserialize(raw);
	std::cout << data->s1 << data->n << data->s2 << std::endl;
	return 0;
}
