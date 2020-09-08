// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/29 19:25:03 by root              #+#    #+#             //
//   Updated: 2018/06/29 19:28:33 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Human.hpp"

int main()
{
	Human	bob;
	Human	jim;

	bob.action("melee", "Jimmy");
	bob.action("ranged", "Jimmy");
	bob.action("shout", "Jimmy");

	jim.action("melee", "Bobby");
	jim.action("ranged", "Bobby");
	jim.action("shout", "Bobby");

	return 0;
}
