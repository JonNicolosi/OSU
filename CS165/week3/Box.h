/*********************************************************************
** Author: Jonathan Nicolosi
** Date: 1/20/2015
** Description: Box Header File
*********************************************************************/

#ifndef BOX_H_INCLUDED
#define BOX_H_INCLUDED

#include <string>
using namespace std;

// Defines the interface of the Box class
class Box
{
private:
//define private variables
    double height;
    double width;
    double length;

public:
    Box();//instantiate box object
    Box(double, double, double);
    void setHeight(double);
    double getHeight();
    void setWidth(double);
    double getWidth();
    void setLength(double);
    double getLength();
    double getVolume();
    double getSurfaceArea();
};


#endif // BOX_H_INCLUDED
