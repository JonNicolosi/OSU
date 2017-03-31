/*********************************************************************
** Author: Jonathan Nicolosi
** Date: 1/20/2015
** Description: Box Implementation
*********************************************************************/

#include <iostream>
#include <string>
#include "Box.hpp"

using namespace std;

Box::Box(){

    setHeight(0); //set data members in default constructor
    setWidth(0);
    setLength(0);

}

Box::Box(double heightIn, double widthIn, double lengthIn){
    setHeight(heightIn);//set the parameters of the constructor
    setWidth(widthIn);
    setLength(lengthIn);
}

//define getters and setters

void Box::setHeight(double heightIn){
    height = heightIn;

}

double Box::getHeight(){
    return height;
}

void Box::setWidth(double widthIn){
    width = widthIn;
}

double Box::getWidth(){
    return width;
}

void Box::setLength(double lengthIn){
    length = lengthIn;
}

double Box::getLength(){
    return length;
}

double Box::getVolume(){
    return length*width*height;
}

double Box::getSurfaceArea(){
    return length*width*6;
}













