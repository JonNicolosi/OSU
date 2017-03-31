/*********************************************************************
** Author: Jonathan Nicolosi
** Date: 2/17/16
** Description: Define MyInteger class
*********************************************************************/
#ifndef MYINTEGER_HPP_INCLUDED
#define MYINTEGER_HPP_INCLUDED

using namespace std;

class MyInteger{

private:
    int *ptr;

public:

    MyInteger(int);
    MyInteger(const MyInteger &obj);
    ~MyInteger();

    int getMyInt();
    void setMyInt(int);

    MyInteger& operator= (const MyInteger &obj);
};


#endif // MYINTEGER_HPP_INCLUDED
