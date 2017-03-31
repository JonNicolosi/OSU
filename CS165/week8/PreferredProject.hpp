/*********************************************************************
** Author: Jonathan Nicolosi
** Date: February 24, 2016
** Description: PreferredProject class designed to return cost of preferred project.
*********************************************************************/

#ifndef PREFERREDPROJECT_HPP_INCLUDED
#define PREFERREDPROJECT_HPP_INCLUDED
#include "CustomerProject.hpp"

class PreferredProject : public CustomerProject{

public:

    PreferredProject():CustomerProject(){
        this->hours = 0;
        this->materials = 0;
        this->transportation = 0;
    }
    PreferredProject(double x, double y, double z):CustomerProject(hours, materials, transportation){
        this->hours = x;
        this->materials = y;
        this->transportation = z;
    }
    double billAmount();
    void setHours(double);
    void setMaterials(double);
    void setTransportation(double);

};




#endif // PREFERREDPROJECT_HPP_INCLUDED
