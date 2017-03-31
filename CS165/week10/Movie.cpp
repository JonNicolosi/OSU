/*********************************************************************
** Author: Jonathan Nicolosi
** Date: March 10, 2016
** Description: Movie class implementation
*********************************************************************/

#include "Movie.hpp"
#include <string>

std::string Movie::getDirector()
{
	return director;
}
int Movie::getCheckOutLength()
{
	return CHECK_OUT_LENGTH;
}
