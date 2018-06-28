// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Account.class.cpp                                  :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2018/06/28 16:36:51 by root              #+#    #+#             //
//   Updated: 2018/06/28 16:48:57 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Account.class.hpp"

Account::Account( void ): _nbAccounts(0), _totalAmount(0), _totalNbDeposits(0),
						  _totalNbWithdrawals(0), _accountIndex(0), _amount(0),
						  _nbDeposits(0), _nbWithdrawals(0)
{}

Account::Account( int initial_deposit )
{}

Account::~Account( void )
{}

static int Account::getNbAccounts( void )
{
	return this->_nbAccounts;
}

static int Account::getTotalAmount( void )
{
	return this->_totalAmount;
}

static int Account::getNbDeposits( void )
{
	return this->_totalNbDeposits;
}

static int Account::getNbWithdrawals( void )
{
	return this->_totalNbWithdrawals;
}

static void Account::displayAccountsInfos( void )
{

}

void Account::makeDeposit( int deposit )
{
	
}
