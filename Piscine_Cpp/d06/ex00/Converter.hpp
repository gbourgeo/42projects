// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Converter.hpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/08 18:01:03 by gbourgeo          #+#    #+#             //
//   Updated: 2018/07/08 22:01:59 by gbourgeo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef CONVERTER_HPP
# define CONVERTER_HPP

#include <string>

class Converter
{
public:
	Converter();
	Converter(Converter const & src);
	Converter & operator=(Converter const & rhs);
	~Converter();

	void	doConversions(std::string const & nb);

private:
	void	doCharConversion();
	void	doIntConversion();
	void	doFloatConversion();
	void	doDoubleConversion();

	std::string		_nb;
	std::string		_conv;
};

#endif
