/*********************************************************************
** Author: Jonathan Nicolosi
** Date: January 27th, 2016
** Description: Define ShoppingCart class
*********************************************************************/

#ifndef SHOPPINGCART_HPP_INCLUDED
#define SHOPPINGCART_HPP_INCLUDED
#include "Item.hpp"



using namespace std;

class ShoppingCart{
private:

    Item * itemArray[100]; //Fill array with pointers to Item object
    static int arrayEnd;

public:

    ShoppingCart(){ //Create default constructor

    }
    //Declare functions
    void addItem(Item*);
    double totalPrice();
};


#endif // SHOPPINGCART_HPP_INCLUDED
