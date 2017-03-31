/*********************************************************************
** Author: Jonathan Nicolosi
** Date: March 10, 2016
** Description: Library class implementation
*********************************************************************/

#include "Library.hpp"
#include "Book.hpp"
#include "Album.hpp"
#include "Movie.hpp"
#include "Patron.hpp"
#include "LibraryItem.hpp"
#include <vector>

#include <iostream>
using namespace std;

Library::Library(){
    currentDate = 0;
}

/*********************************************************************
** Description: Adds an item to the holdigns vector. Takes a pointer
**				to a LibraryItem as a parameter.
*********************************************************************/
void Library::addLibraryItem(LibraryItem* libItem)
{
	libItem->setDateCheckedOut(currentDate);
	holdings.push_back(libItem);
}
/*********************************************************************
** Description: Adds an item to the members vector. Takes a pointer
**				to a Patron as a parameter.
*********************************************************************/
void Library::addPatron(Patron* pat)
{
	members.push_back(pat);
}
/*********************************************************************
** Description: Adds a LibraryItem to a Patron's checked out items.
**				Takes a string representing a patronID and a string
**				representing a LibraryItem ID.
*********************************************************************/
std::string Library::checkOutLibraryItem(std::string patronID, std::string ItemID)
{
	Patron *patPtr;
	LibraryItem *libPtr;
	bool found = false;
	int index = 0;

	while (found == false && index < members.size())
	{
		if (patronID == members[index]->Patron::getIdNum())
		{
			patPtr = members[index];
			found = true;
		}
		index++;
	}
	if (found == false)
		return "patron not found";

	found = false;
	index = 0;
	while (found == false && index < holdings.size())
	{
		if (ItemID == holdings[index]->LibraryItem::getIdCode())
		{
			libPtr = holdings[index];
			if (holdings[index]->LibraryItem::getLocation() == CHECKED_OUT)
			{
				found = true;
				return "item already checked out";
			}
			else if (holdings[index]->LibraryItem::getLocation() == ON_HOLD_SHELF)
			{
				found = true;
				// check LibraryItem was on hold for this patron
					// if it was, set to NULL, check out
				if (holdings[index]->LibraryItem::getRequestedBy() == patPtr)
				{
					holdings[index]->LibraryItem::setCheckedOutBy(patPtr);
					holdings[index]->LibraryItem::setDateCheckedOut(currentDate);
					holdings[index]->LibraryItem::setRequestedBy(NULL);
					patPtr->Patron::addLibraryItem(libPtr);
					holdings[index]->LibraryItem::setLocation(CHECKED_OUT);
					return "check out successful";
				}
				else
					return "item on hold by other patron";
			}
			else		// must be on the shelf
			{
				found = true;
				holdings[index]->LibraryItem::setCheckedOutBy(patPtr);
				holdings[index]->LibraryItem::setDateCheckedOut(currentDate);

				// update Patron's checkedOutItems
				patPtr->Patron::addLibraryItem(libPtr);
				holdings[index]->LibraryItem::setLocation(CHECKED_OUT);
				return "check out successful";
			}
		}
		index++;
	}
	if (found == false)
			return "item not found";
	return "check out not successful";
}
/*********************************************************************
** Description: Returns a LibraryItem from a Patron's checked out
**				items to the Library. Takes as string representing a
**				LibraryItem as a parameter.
*********************************************************************/
std::string Library::returnLibraryItem(std::string ItemID)
{
	bool found = false;
	Patron *patPtr;
	LibraryItem *libPtr;
	int index = 0;

	while (found == false && index < holdings.size())
	{
		if (ItemID == holdings[index]->LibraryItem::getIdCode())
		{
			found = true;
			libPtr = holdings[index];

			if (holdings[index]->LibraryItem::getLocation() == ON_SHELF)
				return "item already in library";
			else if (holdings[index]->LibraryItem::getLocation() == ON_HOLD_SHELF)
				return "item on hold";
		}
		index++;
	}
	if (found == false)
		return "item not found";
	// update the Patron's checkedOutItems
	patPtr = libPtr->LibraryItem::getCheckedOutBy();
	patPtr->Patron::removeLibraryItem(libPtr);
	// update the LibraryItem's location
	if (libPtr->LibraryItem::getRequestedBy() != NULL)
		libPtr->LibraryItem::setLocation(ON_HOLD_SHELF);
	else
		libPtr->LibraryItem::setLocation(ON_SHELF);
	// update the LibraryItem's checkedOutBy
	libPtr->LibraryItem::setCheckedOutBy(NULL);
	return "return successful";
}
/*********************************************************************
** Description: Puts a request hold on a LibraryItem. Takes as a
**				parameter a string representing the ID of the Patron
**				making the request and a string representing the ID
**				of the LibraryItem to be put on hold.
*********************************************************************/
std::string Library::requestLibraryItem(std::string patronID, std::string ItemID)
{
	bool found = false;
	LibraryItem *libPtr;
	Patron *patPtr;

	for (int index = 0; index < holdings.size(); index++)
	{
		if (ItemID == holdings[index]->LibraryItem::getIdCode())
		{
			libPtr = holdings[index];
			found = true;
		}
	}
	if (found == false)
		return "item not found";

	found = false;
	for (int index = 0; index < members.size(); index++)
	{
		if (patronID == members[index]->Patron::getIdNum())
		{
			patPtr = members[index];
			found = true;
		}
	}
	if (found == false)
		return "patron not found";

	if (libPtr->LibraryItem::getLocation() == ON_HOLD_SHELF)
		return "item already on hold";

	libPtr->LibraryItem::setRequestedBy(patPtr);
	if (libPtr->LibraryItem::getLocation() == ON_SHELF)
	{
		libPtr->LibraryItem::setLocation(ON_HOLD_SHELF);
		return "request successful";
	}
	else if (libPtr->LibraryItem::getLocation() == CHECKED_OUT)
		return "request successful";
	return "request not successful";
}
/*********************************************************************
** Description: Reduces a Patron's fine by the amount specified. Takes
**				as a parameter a string representing the Patron's ID
**				and a double representing how much to pay.
*********************************************************************/
std::string Library::payFine(std::string patronID, double payment)
{
	Patron *patPtr;
	bool found = false;

	for (int index = 0; index < members.size(); index++)
	{
		if (patronID == members[index]->Patron::getIdNum())
		{
			patPtr = members[index];
			found = true;
		}
	}
	if (found == false)
		return "patron not found";
	patPtr->Patron::amendFine(-payment);
	return "payment successful";
}
/*********************************************************************
** Description: Adds 1 to the date. Also checks to see if any
**				LibraryItems are now overdue because of the day being
**				incremented.
*********************************************************************/
void Library::incrementCurrentDate()
{
	currentDate++;

	for (int index = 0; index < holdings.size(); index++)
	{
		if (holdings[index]->LibraryItem::getLocation() == CHECKED_OUT)
		{
			if ((currentDate - holdings[index]->LibraryItem::getDateCheckedOut()) > holdings[index]->getCheckOutLength())
			{
				Patron *patPtr = holdings[index]->LibraryItem::getCheckedOutBy();
				patPtr->Patron::amendFine(.10);
			}
		}
	}
}
/*********************************************************************
** Description: Returns a pointer to a Patron. The return value is
**				determined by the parameter passed which is a string
**				representing a Patron's ID.
*********************************************************************/
Patron* Library::getPatron(std::string patronID)
{
	bool found = false;
	int index = 0;
	while (!found && index < members.size())
	{
		if (members[index]->getIdNum() == patronID)
		{
			found = true;
			return members[index];
		}
		else
			index++;
	}
	return NULL;
}
/*********************************************************************
** Description: Returns a pointer to a LibraryItem based on a string
**				representing a LibraryItem ID.
*********************************************************************/
LibraryItem* Library::getLibraryItem(std::string ItemID)
{
	bool found = false;
	int index = 0;
	while (!found && index < holdings.size())
	{
		if (holdings[index]->getIdCode() == ItemID)
		{
			found = true;
			return holdings[index];
		}
		else
			index++;
	}
	return NULL;
}




