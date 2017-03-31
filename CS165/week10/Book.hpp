/*********************************************************************
** Author: Jonathan Nicolosi
** Date: March 10, 2016
** Description: Book class declaration
*********************************************************************/

#ifndef BOOK_HPP
#define BOOK_HPP
#include "LibraryItem.hpp"
#include <string>

class Book : public LibraryItem
{
private:
	std::string author;
public:
	static const int CHECK_OUT_LENGTH = 21;
	// function prototypes
	std::string getAuthor();
	virtual int getCheckOutLength();
	Book(std::string id, std::string title, std::string inAuthor) : LibraryItem(id, title)		// constructor
	{
		author = inAuthor;
	}
};
#endif
