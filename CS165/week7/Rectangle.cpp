/*********************************************************************
** Author: Jonathan Nicolosi
** Date: 2/17/16
** Description: Rectangle class implementation
*********************************************************************/

#include <iostream>
#include <string>
#include "Rectangle.hpp"

using namespace std;

Rectangle::Rectangle(double x, double y){
    length = x;
    width = y;
}

double Rectangle::getLength(){
    return length;
}

double Rectangle::getWidth(){
    return width;
}

void Rectangle::setLength(double lengthIn){
    length = lengthIn;
}

void Rectangle::setWidth(double widthIn){
    width = widthIn;
}
/*********************************************************************
** Description: Functions to compute perimeter and area
**
*********************************************************************/
double Rectangle::perimeter(){
    return 2*(length + width);
}

double Rectangle::area(){
    return length*width;
}
