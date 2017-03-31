/*********************************************************************
** Author: Jonathan Nicolosi
** Date: February 24, 2016
** Description: Base class of program designed to return cost of project.
*********************************************************************/

#ifndef CUSTOMERPROJECT_HPP_INCLUDED
#define CUSTOMERPROJECT_HPP_INCLUDED

using namespace std;

class CustomerProject{

protected:
    double hours;
    double materials;
    double transportation;
public:
    CustomerProject(){
        this->hours = 0;
        this->materials = 0;
        this->transportation = 0;
    }
    CustomerProject(double, double, double);
    double getHours();
    double getMaterials();
    double getTransportation();
    void setHours(double);
    void setMaterials(double);
    void setTransportation(double);
    virtual double billAmount()=0;

};


#endif // CUSTOMERPROJECT_HPP_INCLUDED
