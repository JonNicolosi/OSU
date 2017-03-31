/*********************************************************************
** Author: Jonathan Nicolosi
** Date: 2/3/16
** Description: Box header
*********************************************************************/

#ifndef BOX_HPP_INCLUDED
#define BOX_HPP_INCLUDED

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
    void boxSort(Box[], int);

};

#endif // BOX_HPP_INCLUDED
