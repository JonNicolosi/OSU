#include <iostream>
#include <string>
#include "BankAccount.hpp"

using namespace std;

int main()
{

    BankAccount ba("Jon", "ID: 12345", 50000);


    cout << ba.withdraw(20000) << endl;

    cout << ba.deposit(80000) << endl;

    return 0;
}
