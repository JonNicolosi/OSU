/*********************************************************************
** Author: Jonathan Nicolosi
** Date: January 27th, 2016
** Description: Implement ShoppingCart class
*********************************************************************/

#include <iostream>
#include <iomanip>
#include <string>
#include "ShoppingCart.hpp"

using namespace std;



int ShoppingCart::arrayEnd = 0;
//Function to add items to shopping cart. Passes Item pointer into itemArray and then updates the arrayEnd.
void ShoppingCart::addItem(Item * x){
    itemArray[arrayEnd] = x;
    arrayEnd++;

}



double ShoppingCart::totalPrice(){
    double total = 0;

    for(int h = 0; h<arrayEnd; h++){

        total = total + (itemArray[h]->getPrice())*(itemArray[h]->getQuantity()); //Uses get functions to retrieve values of each item in the itemArray.

    }

    return total;
}




