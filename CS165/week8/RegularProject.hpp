/*********************************************************************
** Author: Jonathan Nicolosi
** Date: February 24, 2016
** Description: RegularProject class designed to return cost of regular project.
*********************************************************************/

#ifndef REGULARPROJECT_HPP_INCLUDED
#define REGULARPROJECT_HPP_INCLUDED
#include "CustomerProject.hpp"
class RegularProject : public CustomerProject{

public:

    RegularProject():CustomerProject(){
        this->hours = 0;
        this->materials = 0;
        this->transportation = 0;
    }
    RegularProject(double x, double y, double z):CustomerProject(hours, materials, transportation){
        this->hours = x;
        this->materials = y;
        this->transportation = z;
    }
    double billAmount();
    void setHours(double);
    void setMaterials(double);
    void setTransportation(double);

};


#endif // REGULARPROJECT_HPP_INCLUDED
