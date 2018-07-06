// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   OfficeBlock.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/06 21:05:27 by root              #+#    #+#             //
//   Updated: 2018/07/06 21:39:15 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef OFFICEBLOCK_HPP
# define OFFICEBLOCK_HPP

#include "Intern.hpp"
#include "Bureaucrat.hpp"

class OfficeBlock
{
public:
	OfficeBlock();
	OfficeBlock(Intern *, Bureaucrat *, Bureaucrat *);
	~OfficeBlock();

	void			setIntern(Intern *);
	void			setSigningBureaucrat(Bureaucrat *);
	void			setExecutingBureaucrat(Bureaucrat *);
	Form *			doBureaucracy(std::string const &, std::string const &);

	class NoInternAssignedException: public std::exception
	{
	public:
		virtual const char * what() const throw()
			{
				return ("Can't do bureaucracy: No intern assigned !");
			}
	};

	class NoSigningBureaucratException: public std::exception
	{
	public:
		virtual const char * what() const throw()
			{
				return ("Can't do bureaucracy: No signing bureaucrat assigned !");
			}
	};

	class NoExecutingBureaucratException: public std::exception
	{
	public:
		virtual const char * what() const throw()
			{
				return ("Can't do bureaucracy: No executing bureaucrat assigned !");
			}
	};

	class NoFormCreatedException: public std::exception
	{
	public:
		virtual const char * what() const throw()
			{
				return ("Can't do bureaucracy: Form doesn't exist !");
			}
	};

	class NoFormSignedException: public std::exception
	{
	public:
		virtual const char * what() const throw()
			{
				return ("form not signed !");
			}
	};

	class NoFormExecutedException: public std::exception
	{
	public:
		virtual const char * what() const throw()
			{
				return ("form not executed !");
			}
	};

private:
	OfficeBlock(OfficeBlock const & src);
	OfficeBlock & operator=(OfficeBlock const & rhs);

	Intern *		_intern;
	Bureaucrat *	_sBureaucrat;
	Bureaucrat *	_xBureaucrat;
};

#endif
