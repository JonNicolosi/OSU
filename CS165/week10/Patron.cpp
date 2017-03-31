/*********************************************************************
** Author: Jonathan Nicolosi
** Date: March 10, 2016
** Description: Patron class implementation
*********************************************************************/

#include "Patron.hpp"
#include <string>
#include <vector>
#include <algorithm>

Patron::Patron(std::string idn, std::string n){
    idNum = idn;
    name = n;
}

std::string Patron::getIdNum()
{
	return idNum;
}
std::string Patron::getName()
{
	return name;
}
std::vector<LibraryItem*> Patron::getCheckedOutItems()
{
	return checkedOutItems;
}
/*********************************************************************
** Description: Adds an item to the checkedOutItems vector. Takes a
**				pointer to a LibraryItem as a parameter.
*********************************************************************/
void Patron::addLibraryItem(LibraryItem* b)
{
	checkedOutItems.push_back(b);
}
/*********************************************************************
** Description: Removes an item from the checkedOutItems vector. Takes
**				a pointer to a LibraryItem as a parameter.
*********************************************************************/
void Patron::removeLibraryItem(LibraryItem* b)
{
	checkedOutItems.erase(std::remove(checkedOutItems.begin(), checkedOutItems.end(), b), checkedOutItems.end());
}
/*********************************************************************
** Description: Returns the Patron's fine amount.
*********************************************************************/
double Patron::getFineAmount()
{
	return fineAmount;
}
/*********************************************************************
** Description: Takes a positive or negative double and amends the
**				Patron's fine by that amount.
*********************************************************************/
void Patron::amendFine(double amount)
{
	fineAmount += amount;
}
