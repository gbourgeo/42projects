// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Contact.hpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/28 12:40:54 by root              #+#    #+#             //
//   Updated: 2018/06/28 14:15:27 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef CONTACT_HPP
# define CONTACT_HPP

# include <string>

class Contact
{
public:
	Contact();
	~Contact();

	void			set_info();
	void			show_min_info();
	void			show_full_info();

private:
	std::string		first_name;
	std::string		last_name;
	std::string		nick_name;
	std::string		login;
	std::string		postal_address;
	std::string		email_address;
	std::string		phone_number;
	std::string		birthday_date;
	std::string		favorite_meal;
	std::string		underwear_color;
	std::string		darkest_secret;
};

#endif
