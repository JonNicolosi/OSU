/*********************************************************************
** Author: Jonathan Nicolosi
** Date: March 10, 2016
** Description: Album class implementation
*********************************************************************/

#include "Album.hpp"
#include <string>

std::string Album::getArtist()
{
	return artist;
}
int Album::getCheckOutLength()
{
	return CHECK_OUT_LENGTH;
}
