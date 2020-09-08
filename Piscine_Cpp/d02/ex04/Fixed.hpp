// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Fixed.hpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/30 17:18:25 by root              #+#    #+#             //
//   Updated: 2018/06/30 19:27:53 by root             ###   ########.fr       //
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
	Fixed & operator++();
	Fixed  operator++(int);
	Fixed & operator--();
	Fixed  operator--(int);

	bool operator<(const  Fixed & rhs) const;
	bool operator>(const  Fixed & rhs) const;
	bool operator<=(const  Fixed & rhs) const;
	bool operator>=(const  Fixed & rhs) const;
	bool operator==(const Fixed & rhs) const;
	bool operator!=(const Fixed & rhs) const;

	Fixed operator+(const Fixed & rhs) const;
	Fixed operator-(const Fixed & rhs) const;
	Fixed operator*(const Fixed & rhs) const;
	Fixed operator/(const Fixed & rhs) const;

	int		getRawBits() const;
	void	setRawBits(int const raw);

	float	toFloat() const;
	int		toInt() const;

	static Fixed &			min(Fixed & a, Fixed & b);
	static Fixed &			max(Fixed & a, Fixed & b);
	static Fixed const &	min(Fixed const & a, Fixed const & b);
	static Fixed const &	max(Fixed const & a, Fixed const & b);
	
private:
	int					_value;
	static const int	_nbBits = 8;
};

std::ostream &	operator<<(std::ostream & o, Fixed const & i);

#endif
