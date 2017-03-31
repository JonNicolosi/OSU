/*********************************************************************
** Author: Jonathan Nicolosi
** Date: February 24, 2016
** Description: PreferredProject implementation.
*********************************************************************/

#include "PreferredProject.hpp"

using namespace std;

void PreferredProject::setHours(double hoursIn){
    hours = hoursIn;
}

void PreferredProject::setMaterials(double materialsIn){
    materials = materialsIn;
}

void PreferredProject::setTransportation(double transportationIn){
    transportation = transportationIn;
}

double PreferredProject :: billAmount(){
    if(hours<100){
        return (80*hours) + (.85*materials) + (.90*transportation);
    }
    else{
        return (80*100) + (.85*materials) + (.90*transportation);
    }

};
