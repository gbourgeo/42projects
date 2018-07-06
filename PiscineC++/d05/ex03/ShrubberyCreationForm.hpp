// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ShrubberyCreationForm.hpp                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/06 16:27:42 by root              #+#    #+#             //
//   Updated: 2018/07/06 17:41:09 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef SHRUBBERYCREATIONFORM_HPP
# define  SHRUBBERYCREATIONFORM_HPP

# include <fstream>
# include "Form.hpp"

# define SHRUBBERY_FORM_SIGN 145
# define SHRUBBERY_FORM_EXEC 137

class ShrubberyCreationForm : public Form
{
public:
	ShrubberyCreationForm(std::string const & target);
	ShrubberyCreationForm(ShrubberyCreationForm const & src);
	ShrubberyCreationForm & operator=(ShrubberyCreationForm const & rhs);
	~ShrubberyCreationForm();

	std::string			getTarget() const;
	void				execute(Bureaucrat const & executor) const;
	
private:
	ShrubberyCreationForm();
	void				setFile(std::ofstream *);

	std::string			_target;
};

#endif
