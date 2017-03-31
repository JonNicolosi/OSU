/*********************************************************************
** Author: Jonathan Nicolosi
** Date: 2/17/16
** Description: Square class declarations
*********************************************************************/

#ifndef SQUARE_HPP_INCLUDED
#define SQUARE_HPP_INCLUDED
#include "Rectangle.hpp"

using namespace std;

class Square : public Rectangle{

public:
    Square() : Rectangle(){
        this->length = 0;
        this->width = 0;
    }
    Square(double side) : Rectangle(length, width){
        this->length = side;
        this->width = side;
    }



    void setLength(double);
    void setWidth(double);

};


#endif // SQUARE_HPP_INCLUDED
