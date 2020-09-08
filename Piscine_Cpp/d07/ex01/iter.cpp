// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   iter.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/09 20:40:06 by gbourgeo          #+#    #+#             //
//   Updated: 2018/07/09 21:16:10 by gbourgeo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>

template<typename T>
void		iter(T *array, size_t arraysize, void (*f)(T &))
{
	for (size_t i = 0; i < arraysize; i++)
		f(array[i]);
}

template<typename T>
void		aff(T &member)
{
	std::cout << member << " ";
}

template<typename T>
void		inc(T &member)
{
	member += 1;
}

int main()
{
	int		inb[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	float	fnb[] = { 1.12, 2.23, 3.34, 4.45, 5.56, 6.67, 7.78, 8.89, 9.90 };
	std::string snb[] = { "salut", "toi", "qui", "lit", "cette", "phrase", "sans", "sens", "." };

	std::cout << "int = ";
	iter(inb, sizeof(inb) / sizeof(*inb), &aff);
	std::cout << std::endl;
	std::cout << "float = ";
	iter(fnb, sizeof(fnb) / sizeof(*fnb), &aff);
	std::cout << std::endl;
	std::cout << "std::string = ";
	iter(snb, sizeof(snb) / sizeof(*snb), &aff);
	std::cout << std::endl;

	iter(inb, sizeof(inb) / sizeof(*inb), &inc);
	iter(fnb, sizeof(fnb) / sizeof(*fnb), &inc);
	iter(snb, sizeof(snb) / sizeof(*snb), &inc);

	std::cout << "int = ";
	iter(inb, sizeof(inb) / sizeof(*inb), &aff);
	std::cout << std::endl;
	std::cout << "float = ";
	iter(fnb, sizeof(fnb) / sizeof(*fnb), &aff);
	std::cout << std::endl;
	std::cout << "std::string = ";
	iter(snb, sizeof(snb) / sizeof(*snb), &aff);
	std::cout << std::endl;

	return 0;
}
