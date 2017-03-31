/*********************************************************************
** Author: Jonathan Nicolosi
** Date: 2/17/16
** Description: Square class implementation
*********************************************************************/

#include "Square.hpp"
#include <iostream>

using namespace std;

void Square::setLength(double lengthIn){
    length = lengthIn;
    width = lengthIn;
}

void Square::setWidth(double widthIn){
    width = widthIn;
    length = widthIn;
}
