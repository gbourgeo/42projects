// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   CentralBureaucracy.hpp                             :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/07/08 03:35:58 by root              #+#    #+#             //
//   Updated: 2018/07/08 06:10:05 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef CENTRALBUREAUCRACY_HPP
# define CENTRALBUREAUCRACY_HPP

# include "OfficeBlock.hpp"

# define OFFICEBLOCKS 20

typedef struct		s_queue
{
	std::string		name;
	struct s_queue	*next;
}					t_queue;

class CentralBureaucracy
{
public:
	CentralBureaucracy();
	CentralBureaucracy(CentralBureaucracy const & src);
	CentralBureaucracy & operator=(CentralBureaucracy const & rhs);
	~CentralBureaucracy();

	void		addBureaucrat(Bureaucrat *);
	void		queueUp(std::string const & person);
	void		doBureaucracy() const;
	OfficeBlock *getBlocks(int) const;
	
private:
	OfficeBlock *	_blocks[OFFICEBLOCKS];
	t_queue *		_queue;
};

#endif
