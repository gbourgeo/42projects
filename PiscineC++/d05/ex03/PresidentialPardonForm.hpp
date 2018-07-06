// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   PresidentialPardonForm.hpp                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/06 16:27:42 by root              #+#    #+#             //
//   Updated: 2018/07/06 17:55:03 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef PRESIDENTIALPARDONFORM_HPP
# define  PRESIDENTIALPARDONFORM_HPP

# include <fstream>
# include "Form.hpp"

# define PRESIDENTIAL_FORM_SIGN 25
# define PRESIDENTIAL_FORM_EXEC 5

class PresidentialPardonForm : public Form
{
public:
	PresidentialPardonForm(std::string const & target);
	PresidentialPardonForm(PresidentialPardonForm const & src);
	PresidentialPardonForm & operator=(PresidentialPardonForm const & rhs);
	~PresidentialPardonForm();

	std::string			getTarget() const;
	void				execute(Bureaucrat const & executor) const;
	
private:
	PresidentialPardonForm();
	void				setFile(std::ofstream *);

	std::string			_target;
};

#endif
