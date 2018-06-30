#include <iostream>
#include "Fixed.hpp"

int main(int ac, char **av)
{
	if (ac != 2 || !*av[1]) {
		std::cout << "Usage:" << std::endl;
		std::cout << "\t" << av[0] << " [expression]" << std::endl;
		return 0;
	}
	
	return 0;
}
