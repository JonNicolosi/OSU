/*********************************************************************
** Author: Jonathan Nicolosi
** Date: 2/17/16
** Description: Rectangle class declarations
*********************************************************************/

#ifndef RETANGLE_HPP_INCLUDED
#define RETANGLE_HPP_INCLUDED
#include <iostream>
#include <string>

using namespace std;

class Rectangle{

protected:
    double length;
    double width;
public:
    Rectangle(){
        this->length = 0;
        this->width = 0;
    }
    Rectangle(double, double);
    double getLength();
    double getWidth();
    void setLength(double);
    void setWidth(double);
    double area();
    double perimeter();

};


#endif // RETANGLE_HPP_INCLUDED
