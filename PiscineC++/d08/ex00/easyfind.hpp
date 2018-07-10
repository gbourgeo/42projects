// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   easyfind.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/10 13:13:54 by root              #+#    #+#             //
//   Updated: 2018/07/10 13:39:53 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef EASYFIND_HPP
# define EASYFIND_HPP

# include <algorithm>
# include <exception>

template<typename T>
typename T::iterator	easyfind(T &array, int nb)
{
	typename T::iterator	it;

	it = std::find(array.begin(), array.end(), nb);
	if (it == array.end())
		throw std::exception();
	return it;
}

#endif
