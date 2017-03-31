/*********************************************************************
** Author: Jonathan Nicolosi
** Date: January 27th, 2016
** Description: Implement Item class
*********************************************************************/

#include <iostream>
#include "Item.hpp"

using namespace std;


//Initialize default constructor

Item::Item(){
    setName("");
    setPrice(0.0);
    setQuantity(0);
}

Item::Item(string nameIn, double priceIn, int quantityIn){
    setName(nameIn);
    setPrice(priceIn);
    setQuantity(quantityIn);
}
//Define getters and setters
void Item::setName(string nameIn){
    name = nameIn;
}

string Item::getName(){
    return name;
}

void Item::setPrice(double priceIn){
    price = priceIn;
}

double Item::getPrice(){
    return price;
}

void Item::setQuantity(int quantityIn){
    quantity = quantityIn;
}

int Item::getQuantity(){
    return quantity;
}

