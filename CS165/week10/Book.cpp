/*********************************************************************
** Author: Jonathan Nicolosi
** Date: March 10, 2016
** Description: Book class implementation
*********************************************************************/

#include "Book.hpp"
#include <string>

std::string Book::getAuthor()
{
	return author;
}
int Book::getCheckOutLength()
{
	return CHECK_OUT_LENGTH;
}
