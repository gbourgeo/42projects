// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   RobotomyRequestForm.hpp                            :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/06 16:27:42 by root              #+#    #+#             //
//   Updated: 2018/07/06 17:39:01 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ROBOTOMYREQUESTFORM_HPP
# define  ROBOTOMYREQUESTFORM_HPP

# include <fstream>
# include "Form.hpp"

# define ROBOTOMY_FORM_SIGN 72
# define ROBOTOMY_FORM_EXEC 45

class RobotomyRequestForm : public Form
{
public:
	RobotomyRequestForm(std::string const & target);
	RobotomyRequestForm(RobotomyRequestForm const & src);
	RobotomyRequestForm & operator=(RobotomyRequestForm const & rhs);
	~RobotomyRequestForm();

	std::string			getTarget() const;
	void				execute(Bureaucrat const & executor) const;
	
private:
	RobotomyRequestForm();
	void				setFile(std::ofstream *);

	std::string			_target;
};

#endif
