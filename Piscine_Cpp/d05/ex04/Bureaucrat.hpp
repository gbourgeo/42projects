// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Bureaucrat.hpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/06 12:10:06 by root              #+#    #+#             //
//   Updated: 2018/07/06 21:24:06 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

# include <iostream>
# include <string>
# include <stdexcept>
# include "Form.hpp"

class Form;

class Bureaucrat
{
public:
	Bureaucrat(std::string const & name, int grade);
	Bureaucrat(Bureaucrat const & src);
	Bureaucrat & operator=(Bureaucrat const & rhs);
	~Bureaucrat();

	std::string const &	getName() const;
	int					getGrade() const;
	void				incrementGrade();
	void				decrementGrade();
	bool				signForm(Form &);
	bool				executeForm(Form const & form);

	class GradeTooHighException : public std::exception
	{
	public:
		virtual const char * what() const throw()
			{
				return ("Bureaucrat: Grade Too High !");
			}
	};

	class GradeTooLowException : public std::exception
	{
	public:
		virtual const char * what() const throw()
			{
				return ("Bureaucrat: Grade Too Low !");
			}
	};

private:
	Bureaucrat();

	std::string	_name;
	int			_grade;
};

std::ostream & operator<<(std::ostream & os, Bureaucrat const & src);

#endif
