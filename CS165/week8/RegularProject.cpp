/*********************************************************************
** Author: Jonathan Nicolosi
** Date: February 24, 2016
** Description: RegularProject implementation.
*********************************************************************/

#include "RegularProject.hpp"

void RegularProject::setHours(double hoursIn){
    hours = hoursIn;
}

void RegularProject::setMaterials(double materialsIn){
    materials = materialsIn;
}

void RegularProject::setTransportation(double transportationIn){
    transportation = transportationIn;
}

double RegularProject :: billAmount(){
    return (80*hours)+materials+transportation;
};
