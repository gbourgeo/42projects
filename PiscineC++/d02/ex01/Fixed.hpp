// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Fixed.hpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/30 17:18:25 by root              #+#    #+#             //
//   Updated: 2018/06/30 18:08:01 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef FIXED_HPP
# define FIXED_HPP

class Fixed
{
public:
	Fixed();
	Fixed(int const raw);
	Fixed(float const raw);
	~Fixed();
	Fixed( Fixed const & src );

	Fixed & operator=(Fixed const & rhs);

	int		getRawBits() const;
	void	setRawBits(int const raw);

	float	toFloat() const;
	int		toInt() const;
private:
	int					_value;
	static const int	_nbBits = 8;
};

std::ostream &	operator<<(std::ostream & o, Fixed const & i);

#endif
