/*********************************************************************
** Author: Jonathan Nicolosi
** Date: 1/20/2015
** Description: BankAccount Header File
*********************************************************************/


#ifndef BANKACCOUNT_HPP_INCLUDED
#define BANKACCOUNT_HPP_INCLUDED

#include <string>

using namespace std;

class BankAccount{

private:
//declare private variables
    string customerName;
    string customerID;
    double customerBalance;

public:
    BankAccount(); //instantiate constructor
    BankAccount(string s1, string s2, double d){//initialize a parameterized constructor
        customerName = s1;
        customerID = s2;
        customerBalance = d;
    }
    //initialize functions
    string getCustomerName();
    string getCustomerID();
    double getCustomerBalance();
    double withdraw(double);
    double deposit(double);

};



#endif // BANKACCOUNT_H_INCLUDED
