/*********************************************************************
** Author: Jonathan Nicolosi
** Date: January 27th, 2016
** Description: Define Item class
*********************************************************************/

#ifndef ITEM_HPP_INCLUDED
#define ITEM_HPP_INCLUDED

using namespace std;

class Item{

private:
    string name;
    double price;
    int quantity;

public:
    Item(); //Create default constructor
    Item(string, double, int);
    void setName(string);
    void setPrice(double);
    void setQuantity(int);
    string getName();
    double getPrice();
    int getQuantity();

};

#endif // ITEM_HPP_INCLUDED
