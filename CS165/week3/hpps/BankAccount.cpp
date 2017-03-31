/*********************************************************************
** Author: Jonathan Nicolosi
** Date: 1/20/2015
** Description: Bank Account implementation
*********************************************************************/

#include <iostream>
#include <string>
#include "BankAccount.hpp"

using namespace std;


//define functions

string BankAccount::getCustomerName(){
    return customerName;
}

string BankAccount::getCustomerID(){
    return customerID;
}

double BankAccount::getCustomerBalance(){
    return customerBalance;
}

double BankAccount::withdraw(double w){
    return customerBalance - w;
}

double BankAccount::deposit(double d){
    return customerBalance + d;
}




