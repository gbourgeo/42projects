// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Fixed.hpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/30 17:18:25 by root              #+#    #+#             //
//   Updated: 2018/06/30 17:39:19 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FIXED_HPP
# define FIXED_HPP

class Fixed
{
public:
	Fixed();
	~Fixed();
	Fixed( Fixed const & src );

	Fixed & operator=(Fixed const & rhs);

	int		getRawBits() const;
	void	setRawBits(int const raw);

private:
	int					_value;
	static const int	_nbBits = 8;
};

#endif
