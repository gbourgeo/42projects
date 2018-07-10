// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   span.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/10 13:41:12 by root              #+#    #+#             //
//   Updated: 2018/07/10 14:18:47 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef SPAN_HPP
# define SPAN_HPP

# include <list>
# include <exception>

class Span
{
public:
	Span(unsigned int N);
	Span(Span const & src);
	Span & operator=(Span const & rhs);
	~Span();

	std::list<int>	getElems() const;
	unsigned int	getNbElems() const;
	void			addNumber(int nb);
	int				shortestSpan() const;
	int				longestSpan() const;
	
private:
	Span();

	std::list<int>	_elems;
	unsigned int	_nbElems;
};

#endif
