/*********************************************************************
** Author: Jonathan Nicolosi
** Date: 2/17/16
** Description: Define functions for MyInteger class
*********************************************************************/

#include "MyInteger.hpp"
#include <iostream>

using namespace std;

/*********************************************************************
** Description: Define default constructor for MyInteger
**
*********************************************************************/
MyInteger::MyInteger(int x){
    ptr = new int;
    *ptr = x;
}
/*********************************************************************
** Description: Define MyInteger copy constructor
**
*********************************************************************/
MyInteger::MyInteger(const MyInteger &obj){

    ptr = new int;
    *ptr = *(obj.ptr);

}
/*********************************************************************
** Description: Define MyInteger destructor
**
*********************************************************************/
MyInteger::~MyInteger(void){
    delete ptr;
}
/*********************************************************************
** Description: Overload = operator
**
*********************************************************************/
MyInteger& MyInteger::operator= (const MyInteger &obj){

    if(this == &obj){
        return *this;
    }
    *ptr = *obj.ptr;
    return *this;
}

void MyInteger::setMyInt(int integer){
    *ptr = integer;
}

int MyInteger::getMyInt(){
    return *ptr;
}
