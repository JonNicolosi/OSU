/*********************************************************************
** Author: Jonathan Nicolosi
** Date: February 24, 2016
** Description: CustomerProject implementation
*********************************************************************/

#include "CustomerProject.hpp"

using namespace std;

CustomerProject::CustomerProject(double x, double y, double z){
    hours = x;
    materials = y;
    transportation = z;
}

double CustomerProject::getHours(){
    return hours;
}

double CustomerProject::getMaterials(){
    return materials;
}

double CustomerProject::getTransportation(){
    return transportation;
}

void CustomerProject::setHours(double hoursIn){
    hours = hoursIn;
}

void CustomerProject::setMaterials(double materialsIn){
    materials = materialsIn;
}

void CustomerProject::setTransportation(double transportationIn){
    transportation = transportationIn;
}


